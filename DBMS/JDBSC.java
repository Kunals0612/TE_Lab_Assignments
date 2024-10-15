

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.ResultSet;
import java.sql.PreparedStatement;
import java.util.Scanner;

public class JDBSC {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int choice;
        
        do {
            System.out.println("\nMenu:");
            System.out.println("1. Create Table");
            System.out.println("2. Insert Record");
            System.out.println("3. Update Record");
            System.out.println("4. Display Records");
            System.out.println("5. Delete Record");
            System.out.println("6. Exit");
            System.out.print("Enter your choice: ");
            choice = scanner.nextInt();
            
            switch (choice) {
                case 1:
                    createTable();
                    break;
                case 2:
                    insertRecord();
                    break;
                case 3:
                    updateRecord();
                    break;
                case 4:
                    displayRecords();
                    break;
                case 5:
                    deleteRecord();
                    break;
                case 6:
                    System.out.println("Exiting...");
                    break;
                default:
                    System.out.println("Invalid choice! Please try again.");
            }
        } while (choice != 6);
        
        scanner.close();
    }

    public static void createTable() {
        // Define your connection URL
        String url = "jdbc:mysql://10.10.13.97:3306/te31172_db";
        String user = "te31172";
        String password = "te31172";
        
        try {
            Class.forName("com.mysql.jdbc.Driver");
            try (Connection con = DriverManager.getConnection(url, user, password)) {
                if (con != null && !con.isClosed()) {
                    Statement stmt = con.createStatement();
                    String createQuery = "CREATE TABLE IF NOT EXISTS classRoom(roll_no INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(50))";
                    stmt.executeUpdate(createQuery);
                    System.out.println("Table classRoom created successfully.");
                }
            }
        } catch (ClassNotFoundException | SQLException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    public static void insertRecord() {
        String url = "jdbc:mysql://10.10.13.97:3306/te31172_db";
        String user = "te31172";
        String password = "te31172";
        Scanner scanner = new Scanner(System.in);

        try {
            Class.forName("com.mysql.jdbc.Driver");
            try (Connection con = DriverManager.getConnection(url, user, password)) {
                if (con != null && !con.isClosed()) {
                    System.out.print("Enter name: ");
                    String name = scanner.nextLine();

                    String insertQuery = "INSERT INTO classRoom (name) VALUES (?)";
                    try (PreparedStatement pstmt = con.prepareStatement(insertQuery)) {
                        pstmt.setString(1, name);
                        int rowsAffected = pstmt.executeUpdate();
                        System.out.println("Inserted " + rowsAffected + " row(s) into the classRoom table.");
                    }
                }
            }
        } catch (ClassNotFoundException | SQLException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    public static void updateRecord() {
        String url = "jdbc:mysql://10.10.13.97:3306/te31172_db";
        String user = "te31172";
        String password = "te31172";
        Scanner scanner = new Scanner(System.in);

        try {
            Class.forName("com.mysql.jdbc.Driver");
            try (Connection con = DriverManager.getConnection(url, user, password)) {
                if (con != null && !con.isClosed()) {
                    System.out.print("Enter roll_no to update: ");
                    int roll_no = scanner.nextInt();
                    scanner.nextLine();  // Consume newline

                    System.out.print("Enter new name: ");
                    String newName = scanner.nextLine();

                    String updateQuery = "UPDATE classRoom SET name = ? WHERE roll_no = ?";
                    try (PreparedStatement pstmt = con.prepareStatement(updateQuery)) {
                        pstmt.setString(1, newName);
                        pstmt.setInt(2, roll_no);
                        int rowsAffected = pstmt.executeUpdate();
                        System.out.println("Updated " + rowsAffected + " row(s) in the classRoom table.");
                    }
                }
            }
        } catch (ClassNotFoundException | SQLException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    public static void displayRecords() {
        String url = "jdbc:mysql://10.10.13.97:3306/te31172_db";
        String user = "te31172";
        String password = "te31172";

        try {
            Class.forName("com.mysql.jdbc.Driver");
            try (Connection con = DriverManager.getConnection(url, user, password)) {
                if (con != null && !con.isClosed()) {
                    String selectQuery = "SELECT * FROM classRoom";
                    try (Statement stmt = con.createStatement();
                         ResultSet rs = stmt.executeQuery(selectQuery)) {
                        System.out.println("Displaying data from classRoom table:");
                        while (rs.next()) {
                            int roll_no = rs.getInt("roll_no");
                            String name = rs.getString("name");
                            System.out.printf("roll_no: %d, Name: %s%n", roll_no, name);
                        }
                    }
                }
            }
        } catch (ClassNotFoundException | SQLException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    public static void deleteRecord() {
        String url = "jdbc:mysql://10.10.13.97:3306/te31172_db";
        String user = "te31172";
        String password = "te31172";
        Scanner scanner = new Scanner(System.in);

        try {
            Class.forName("com.mysql.jdbc.Driver");
            try (Connection con = DriverManager.getConnection(url, user, password)) {
                if (con != null && !con.isClosed()) {
                    System.out.print("Enter roll_no to delete: ");
                    int roll_no = scanner.nextInt();

                    String deleteQuery = "DELETE FROM classRoom WHERE roll_no = ?";
                    try (PreparedStatement pstmt = con.prepareStatement(deleteQuery)) {
                        pstmt.setInt(1, roll_no);
                        int rowsAffected = pstmt.executeUpdate();
                        if (rowsAffected > 0) {
                            System.out.println("Deleted successfully.");
                        } else {
                            System.out.println("No record found with the given roll_no.");
                        }
                    }
                }
            }
        } catch (ClassNotFoundException | SQLException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
