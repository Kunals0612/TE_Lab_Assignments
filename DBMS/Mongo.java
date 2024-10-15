import java.util.*;

import com.mongodb.MongoClient;
import com.mongodb.client.*;
import com.mongodb.client.result.UpdateResult;
import com.mongodb.MongoCredential;
import com.mongodb.ServerAddress;
import org.bson.Document;

public class Mongo {
    public static void main(String[] args) {
        MongoCredential credentials = MongoCredential.createCredential("te31172", "te31172_db",
                "te31172".toCharArray());
        MongoClient client = new MongoClient(new ServerAddress("10.10.13.97", 27017), Arrays.asList(credentials));
        System.out.println("Connected To Database");
        MongoDatabase db = client.getDatabase("te31172_db");
        MongoCollection<Document> collection = db.getCollection("Test");

        Scanner sc = new Scanner(System.in);
        while (true) {

            System.out.println("Menu:");
            System.out.println("1. Create");
            System.out.println("2. Read");
            System.out.println("3. Update");
            System.out.println("4. Delete");
            System.out.println("5. Exit");
            System.out.println("Enter choice: ");
            int choice = sc.nextInt();

            switch (choice) {
                case 1:
                    insertDocument(collection, sc);
                    break;
                case 2:
                    readDocument(collection, sc);
                    break;
                case 3:
                    updateDocument(collection, sc);
                    break;
                case 4:
                    deleteDocument(collection, sc);
                    break;
                case 5:
                    break;

            }
        }

    }

    public static void insertDocument(MongoCollection<Document> collection, Scanner sc) {
        System.out.println("Enter Name: ");
        String name = sc.next();
        System.out.println("Enter Marks: ");
        String marks = sc.next();
        Document newdoc = new Document("Name", name).append("Marks", marks);
        collection.insertOne(newdoc);
        System.out.println("Inserted Successfully");
    }

    public static void readDocument(MongoCollection<Document> collection, Scanner sc) {
        for (Document doc : collection.find()) {
            System.out.println(doc.toJson());
        }
    }

    public static void updateDocument(MongoCollection<Document> collection, Scanner sc) {
        System.out.println("Enter Name: ");
        String name = sc.next();
        System.out.println("Enter Marks: ");
        String marks = sc.next();
        Document doc = new Document("Name", name);
        Document update = new Document("$set", new Document("Marks", marks));

        collection.updateOne(doc, update);

        System.out.println("Updated Successfully");

    }

    public static void deleteDocument(MongoCollection<Document> collection, Scanner sc) {
        System.out.println("Enter Name: ");
        String name = sc.next();
        Document filter = new Document("Name", name);
        collection.deleteOne(filter);
        System.out.println("Document Deleted Successfully");
    }
}
