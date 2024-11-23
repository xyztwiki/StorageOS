package IOStream
import java.io.*;
public class IOStream{
    public static void main(String[] args) {
        String inputFileName = "input.txt";
        String outputFileName = "output.txt";

        try (OutputStream outputStream = new FileOutputStream(outputFileName)) {
            String content = "Hello, this is a test of Java OutputStream!\n" +
                             "We're writing this content to a file.";
            byte[] contentBytes = content.getBytes();
            outputStream.write(contentBytes);
            System.out.println("Successfully wrote to the file: " + outputFileName);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
        }

        try (InputStream inputStream = new FileInputStream(inputFileName)) {
            System.out.println("\nReading from file: " + inputFileName);
            System.out.println("File content:");

            int data;
            while ((data = inputStream.read()) != -1) {
                System.out.print((char) data);
            }
        } catch (IOException e) {
            System.err.println("An error occurred while reading the file: " + e.getMessage());
        }

        try (InputStream inputStream = new FileInputStream(inputFileName);
             OutputStream outputStream = new FileOutputStream(outputFileName, true)) { // Append mode

            System.out.println("\n\nCopying content from " + inputFileName + " to " + outputFileName);

            byte[] buffer = new byte[1024];
            int bytesRead;

            outputStream.write("\n\n--- Copied Content ---\n".getBytes());

            while ((bytesRead = inputStream.read(buffer)) != -1) {
                outputStream.write(buffer, 0, bytesRead);
            }

            System.out.println("File copied successfully!");
        } catch (IOException e) {
            System.err.println("An error occurred while copying the file: " + e.getMessage());
        }
        
        System.out.println("\nFinal content of " + outputFileName + ":");
        try (BufferedReader reader = new BufferedReader(new FileReader(outputFileName))) {
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            System.err.println("An error occurred while reading the final output: " + e.getMessage());
        }
    }
}
