// Insert multiple student records into the 'students' collection.
db.students.insertMany([
  { name: "John Doe", marks: 85 },
  { name: "Jane Smith", marks: 92 },
  { name: "Sam Brown", marks: 78 },
  { name: "Lucy Adams", marks: 88 },
  { name: "Tom Harris", marks: 90 },
  { name: "Sara White", marks: 81 },
  { name: "Mike Johnson", marks: 75 },
  { name: "Emily Davis", marks: 95 },
  { name: "David Lee", marks: 95 },
  { name: "Olivia Clark", marks: 84 }
]); // Inserts 10 student records with 'name' and 'marks'.

// Count total number of documents in the 'students' collection.
db.students.countDocuments(); 

// Count the number of documents where the marks are 95.
db.students.countDocuments({"marks": 95});

// Group the documents by the 'marks' field, creating distinct groups for each unique 'marks' value.
db.students.aggregate(
  [{ $group: { _id: "$marks" }}]
);

// Limit the output to only 1 document.
db.students.aggregate(
  [{$limit: 1}]
);

// Project only the 'name' field for each document and limit the output to 5 documents.
db.students.aggregate(
  [
    { $project: { "name": 1 }},
    { $limit: 5 }
  ]
);

// Sort the documents in descending order by 'marks'.
db.students.aggregate(
  { $sort: { marks: -1 } }
);

// Filter the documents where 'marks' is greater than 90.
db.students.aggregate(
  { $match: { marks: { $gt: 90 } } }
);

// Create a unique index on the 'name' field to prevent duplicate names.
db.students.createIndex({ name: 1 }, { unique: true }); 
// Explanation: This index ensures that no two students can have the same name, enforcing data integrity.

// Create a compound index on 'marks' and 'name' fields to optimize queries involving both.
db.students.createIndex({ marks: -1, name: 1 }); 
// Explanation: This compound index sorts 'marks' in descending order and 'name' in ascending order, which is useful for queries that sort or filter based on both fields.

// Returns a list of all the indexes currently on the 'students' collection.
db.students.getIndexes(); 

// Drops the index on the 'name' field.
db.students.dropIndex({ name: 1 });

// Returns the updated list of indexes after the previous index was dropped.
db.students.getIndexes(); 

// Example of a unique compound index that enforces unique names for students with the same marks.
db.students.createIndex({ marks: 1, name: 1 }, { unique: true });
// Explanation: This unique compound index enforces uniqueness across the combination of 'marks' and 'name', which means that if two students have the same marks, they cannot have the same name. 

// Calculate the sum of all student marks.
db.students.aggregate([
  { $group: { _id: null, totalMarks: { $sum: "$marks" } } }
]);
// Explanation: This aggregation calculates the total sum of the 'marks' field across all documents.

// Calculate the average of all student marks.
db.students.aggregate([
  { $group: { _id: null, averageMarks: { $avg: "$marks" } } }
]);
// Explanation: This aggregation calculates the average of the 'marks' field across all documents.
