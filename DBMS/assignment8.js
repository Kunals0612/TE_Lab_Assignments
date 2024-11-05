// Create Collection
db.createCollection("students");

// Insert documents into the students collection
db.students.insertMany([
    { "id": 1, "name": "Alice", "age": 20, "courses": ["Math", "Science", "English"] },
    { "id": 2, "name": "Bob", "age": 22, "courses": ["History", "Art"] },
    { "id": 3, "name": "Charlie", "age": 21, "courses": ["Computer Science", "Mathematics"] },
    { "id": 4, "name": "David", "age": 22, "courses": ["Math", "History"] }
]);

// Read all documents in the students collection
db.students.find().pretty();

// Find based on Id
db.students.find({"id": 3});
// Update a student's courses (Alice)
db.students.updateOne(
    { "name": "Alice" }, // Filter to find Alice
    { $set: { "courses": ["Biology", "Physics"] } } // Update to new courses
);

// Update all students' courses who are taking "Math"
db.students.updateMany(
    { "courses": "Math" }, // Filter for students taking Math
    { $push: { "courses": "Advanced Math" } } // Add "Advanced Math" to their courses
);

// Read documents after updates
db.students.find().pretty();

// Delete students whose name is "Alice"
db.students.deleteMany({ "name": "Alice" });

// Read documents after the deletion
db.students.find().pretty();

// Example of deleting multiple students with age 23
db.students.deleteMany({ "age": 23 });

// Final read to show remaining students
db.students.find().pretty();
