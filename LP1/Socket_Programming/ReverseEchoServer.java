import java.io.*;
import java.net.*;

// ClientHandler class to handle each client in a separate thread
class ClientHandler implements Runnable {
    private final Socket clientSocket;

    public ClientHandler(Socket socket) {
        this.clientSocket = socket;
    }

    @Override
    public void run() {
        try (
            BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true)
        ) {
            String message;
            while ((message = in.readLine()) != null) {  // Read message from client
                if (message.equalsIgnoreCase("end")) {  // Exit if the message is "end"
                    break;
                }

                // Reverse the message
                String reversedMessage = new StringBuilder(message).reverse().toString();
                System.out.println("Received from client: " + message + " | Reversed: " + reversedMessage);

                // Send the reversed message back to the client
                out.println(reversedMessage);
            }
        } catch (IOException e) {
            System.out.println("Client disconnected: " + e.getMessage());
        } finally {
            try {
                clientSocket.close();
            } catch (IOException e) {
                System.out.println("Error closing client socket: " + e.getMessage());
            }
        }
    }
}

public class ReverseEchoServer{
    private static final int PORT = 2000;

    public static void main(String[] args) {
        System.out.println("Server started on port " + PORT);

        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            while (true) {
                // Accept new client connections
                Socket clientSocket = serverSocket.accept();
                System.out.println("New client connected: " + clientSocket.getRemoteSocketAddress());

                // Create a new thread for each client connection
                Thread clientThread = new Thread(new ClientHandler(clientSocket));
                clientThread.start();
            }
        } catch (IOException e) {
            System.out.println("Server error: " + e.getMessage());
        }
    }
}



class Client {
    private static final String SERVER_ADDRESS = "localhost";
    private static final int SERVER_PORT = 2000;

    public static void main(String[] args) {
        try (Socket socket = new Socket(SERVER_ADDRESS, SERVER_PORT);
             BufferedReader userInput = new BufferedReader(new InputStreamReader(System.in));
             BufferedReader serverInput = new BufferedReader(new InputStreamReader(socket.getInputStream()));
             PrintWriter serverOutput = new PrintWriter(socket.getOutputStream(), true)
        ) {
            System.out.println("Connected to the server. Type your messages (type 'end' to quit):");

            String message;
            while (true) {
                System.out.print("Enter message: ");
                message = userInput.readLine();

                // Send message to the server
                serverOutput.println(message);

                if (message.equalsIgnoreCase("end")) {
                    break;
                }

                // Receive and print the reversed message from the server
                String reversedMessage = serverInput.readLine();
                System.out.println("Reversed from server: " + reversedMessage);
            }
        } catch (IOException e) {
            System.out.println("Client error: " + e.getMessage());
        }
    }
}
