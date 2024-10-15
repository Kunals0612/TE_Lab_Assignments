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
]);
// Inserts 10 student records with 'name' and 'marks'.

db.students.aggregate(
  [{ $group: {_id: "$marks"}}]
);
// Groups the documents by the 'marks' field, creating distinct groups for each unique 'marks' value.

db.students.aggregate(
  [{$limit: 1}]
);
// Limits the output to only 1 document.

db.students.aggregate(
  [
    { $project: { "name": 1 }},
    { $limit: 5 }
  ]
);
// Projects only the 'name' field for each document and limits the output to 5 documents.

db.students.aggregate(
  { $sort: {marks: -1} }
);
// Sorts the documents in descending order by 'marks'.

db.students.aggregate(
  { $match: { marks: { $gt: 90 } } }
);
// Filters the documents where 'marks' is greater than 90.

db.students.createIndex({ name: 1 });
// Creates an ascending index on the 'name' field to optimize searches based on 'name'.

db.students.getIndexes();
// Returns a list of all the indexes currently on the 'students' collection.

db.students.dropIndex({ name: 1 });
// Drops the index on the 'name' field.

db.students.getIndexes();
// Returns the updated list of indexes after the previous index was dropped.
