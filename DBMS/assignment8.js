// Create Collection
db.createCollection("students");

// Insert documents into the students collection with composite name fields
db.students.insertMany([
    { "id": 1, "name": { "fname": "Alice", "lname": "Smith" }, "age": 20, "courses": ["Math", "Science", "English"] },
    { "id": 2, "name": { "fname": "Bob", "lname": "Johnson" }, "age": 22, "courses": ["History", "Art"] },
    { "id": 3, "name": { "fname": "Charlie", "lname": "Brown" }, "age": 21, "courses": ["Computer Science", "Mathematics"] },
    { "id": 4, "name": { "fname": "David", "lname": "Williams" }, "age": 22, "courses": ["Math", "History"] }
]);

// Read all documents in the students collection
db.students.find().pretty();

// Find based on Id
db.students.find({ "id": 3 });

db.students.find({
    $and: [
        { "courses": "Math" },  // The student must be taking Math
        { "age": 22 }           // The student must be 22 years old
    ]
}).pretty();

db.students.find({
    $or: [
        { "age": 21 },             // The student must be 21 years old
        { "courses": "History" }   // The student must be taking History
    ]
}).pretty();

db.students.find({
    "courses": { $not: { $eq: "Math" } }  // Inverts the condition to find students not taking Math
}).pretty();


// Update a student's courses (Alice)
db.students.updateOne(
    { "name.fname": "Alice" }, // Filter to find Alice using fname
    { $set: { "courses": ["Biology", "Physics"] } } // Update to new courses
);

// Update all students' courses who are taking "Math"
db.students.updateMany(
    { "courses": "Math" }, // Filter for students taking Math
    { $push: { "courses": "Advanced Math" } } // Add "Advanced Math" to their courses
);

// Read documents after updates
db.students.find().pretty();

// Delete students whose first name is "Alice"
db.students.deleteMany({ "name.fname": "Alice" });

// Read documents after the deletion
db.students.find().pretty();

// Example of deleting multiple students with age 23
db.students.deleteMany({ "age": 23 });

// Final read to show remaining students
db.students.find().pretty();




