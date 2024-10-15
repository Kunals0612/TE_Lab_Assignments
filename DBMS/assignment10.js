db.sales.insertMany([
    { "id": 1, "product": "Laptop", "price": 800, "quantity": 2 },
    { "id": 2, "product": "Phone", "price": 500, "quantity": 5 },
    { "id": 3, "product": "Laptop", "price": 800, "quantity": 1 },
    { "id": 4, "product": "Tablet", "price": 300, "quantity": 3 },
    { "id": 5, "product": "Phone", "price": 500, "quantity": 2 }
])


db.sales.mapReduce(
    function() { 
        emit(this.product, this.quantity);  
    },
    function(key, values) { 
        return Array.sum(values);  
    }, 
    {
         
        out: "post_total",
        verbose:true
                             
    }
);

db.post_total.find()