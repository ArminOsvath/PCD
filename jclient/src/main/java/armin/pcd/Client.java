package armin.pcd;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileOutputStream;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.stream.Stream;

import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.DefaultParser;
import org.apache.commons.cli.Option;
import org.apache.commons.cli.Options;

public final class Client {
    public static void main(String[] args) throws Exception {
        CommandLineParser parser = new DefaultParser();
        CommandLine line = parser.parse(buildOptions(), args);
        String image = line.getOptionValue("I");
        Path imagePath = Paths.get(image);
        Filter filter = getFilter(line);

        try (Socket socket = new Socket("localhost", 9326)) {
            DataOutputStream outputStream = new DataOutputStream(socket.getOutputStream());

            String message = "message";
            byte[] messageBytes = new byte[1025];
            System.arraycopy(message.getBytes(), 0, messageBytes, 0, message.length());
            outputStream.write(messageBytes);

            byte[] pwd = new byte[4];
            for (int i = 0; i < 4; i++)
                pwd[i] = 0;
            outputStream.write(pwd);

            byte[] imgNameBytes = new byte[2048];
            System.arraycopy(image.getBytes(), 0, imgNameBytes, 0, image.length());
            outputStream.write(imgNameBytes);

            byte[] filterBytes = new byte[16];
            writeFilter(filterBytes, 0, filter.isVerbose);
            writeFilter(filterBytes, 1, filter.isGray);
            writeFilter(filterBytes, 2, filter.isBinary);
            writeFilter(filterBytes, 3, filter.isBlur);
            writeFilter(filterBytes, 4, filter.isContour);
            writeFilter(filterBytes, 5, filter.isEqHis);
            writeFilter(filterBytes, 6, filter.isGblur);
            writeFilter(filterBytes, 7, filter.isHSV);
            writeFilter(filterBytes, 8, filter.isMedian);
            writeFilter(filterBytes, 9, filter.isSobel);
            filterBytes[12] = (byte) filter.filterCounter;
            outputStream.write(filterBytes);

            long size = Files.size(imagePath);

            byte[] sizeBytes = new byte[8];
            for (int i = 0; i < 8; i++)
                writeSize(sizeBytes, i, size);
            outputStream.write(sizeBytes);
            outputStream.write(Files.readAllBytes(imagePath));

            DataInputStream inputStream = new DataInputStream(socket.getInputStream());

            for (int i = 0; i < filter.filterCounter; i++) {

                byte[] newImageNameBytes = new byte[2048];
                inputStream.read(newImageNameBytes, 0, 2048);
                String newImageName = new String(newImageNameBytes).trim();
                
                byte[] newImageSizeBytes = new byte[8];
                inputStream.read(newImageSizeBytes, 0, 8);
                long newImageSize = readSize(newImageSizeBytes);
                System.out.println("new name is: " + newImageName);
                System.out.println("new size is: " + newImageSize);
                System.out.println(java.util.Arrays.toString(newImageSizeBytes));


                try (FileOutputStream fileOutputStream = new FileOutputStream(
                        imagePath.toAbsolutePath().getParent().resolve(newImageName).toFile());
                        FileChannel fileChannel = fileOutputStream.getChannel()) {

                    long offset = 0;
                    while (newImageSize > 0) {
                        int bytesToRead = newImageSize > (long) Integer.MAX_VALUE ? Integer.MAX_VALUE : (int) newImageSize;
                        newImageSize -= bytesToRead;
                        byte[] newImageBytes = new byte[bytesToRead];
                        inputStream.read(newImageBytes, 0, bytesToRead);
                        fileChannel.position(offset);
                        fileChannel.write(ByteBuffer.wrap(newImageBytes));
                        offset += bytesToRead;
                    }
                }

            }
        }
    }

    private static long readSize(byte[] array) {
        long size = array[0] >= 0 ? array[0] : 256 + array[0];
        for (int i = 1; i < 8; i++)
            size += (array[i] >= 0 ? array[i] : 256 + array[i])  * 256 * i;
        return size;
    }

    private static byte writeSize(byte[] array, int position, long value) {
        return array[position] = (byte) ((value >> (8 * position)) & 0xff);
    }

    private static byte writeFilter(byte[] array, int position, boolean condition) {
        return array[position] = (byte) (condition ? 1 : 0);
    }

    private static Filter getFilter(CommandLine line) throws Exception {
        Filter filter = new Filter();
        if (line.getOptionValue("v").equals("1"))
            filter.isVerbose = true;
        else if (line.getOptionValue("v").equals("0"))
            filter.isVerbose = false;
        else
            throw new Exception("Invalid value for verbose: '" + line.getOptionValue("v") + "'");

        filter.isBinary = line.hasOption("b");
        filter.isBlur = line.hasOption("B");
        filter.isContour = line.hasOption("c");
        filter.isEqHis = line.hasOption("e");
        filter.isGblur = line.hasOption("G");
        filter.isGray = line.hasOption("g");
        filter.isHSV = line.hasOption("h");
        filter.isMedian = line.hasOption("m");
        filter.isSobel = line.hasOption("s");
        filter.filterCounter = (int) Stream.of(filter.isBinary, filter.isBlur, filter.isContour, filter.isEqHis,
                filter.isGblur, filter.isGray, filter.isHSV, filter.isMedian, filter.isSobel)
                .filter(option -> option == true).count() +1;
        return filter;
    }

    private static Options buildOptions() {
        Options options = new Options();
        options.addOption(Option.builder("I").desc("Image path").hasArg().required().build());
        options.addOption(Option.builder("v").desc("Verbose (1/0)").hasArg().required().build());
        options.addOption(Option.builder("b").desc("binary").build());
        options.addOption(Option.builder("B").desc("blur").build());
        options.addOption(Option.builder("c").desc("contour").build());
        options.addOption(Option.builder("e").desc("equalized histogram").build());
        options.addOption(Option.builder("G").desc("gaussian blur").build());
        options.addOption(Option.builder("g").desc("gray").build());
        options.addOption(Option.builder("h").desc("HSV").build());
        options.addOption(Option.builder("m").desc("median").build());
        options.addOption(Option.builder("s").desc("sobel").build());
        return options;
    }

    static class Filter {
        boolean isVerbose;
        boolean isGray;
        boolean isBinary;
        boolean isBlur;
        boolean isContour;
        boolean isEqHis;
        boolean isGblur;
        boolean isHSV;
        boolean isMedian;
        boolean isSobel;
        int filterCounter;
    }
}
