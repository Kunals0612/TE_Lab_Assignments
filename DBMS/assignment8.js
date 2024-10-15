
// create
db.employees.insertMany([
    {empId: 1, name: 'Clark', dept: 'Sales' },
    {empId: 2, name: 'Dave', dept: 'Accounting' },
    {empId: 3, name: 'Ava', dept: 'Sales' }
  ]);
  
  // Read
  db.employees.find();
  
  // Read one 
  db.employees.find({empId:1});
  
  // update
  db.employees.update({empId: 1}, {$set: {name: "Kunal"}});
  db.employees.find();
  
  // delete
  db.employees.remove({empId: 3});
  db.employees.find();