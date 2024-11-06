db.sales.insertMany([
    { 
        "id": 1, 
        "product": "Laptop", 
        "price": 800, 
        "quantity": 2, 
        "date": { "year": 2024, "month": 1 }
    },
    { 
        "id": 2, 
        "product": "Phone", 
        "price": 500, 
        "quantity": 5, 
        "date": { "year": 2024, "month": 1 }
    },
    { 
        "id": 3, 
        "product": "Laptop", 
        "price": 800, 
        "quantity": 1, 
        "date": { "year": 2024, "month": 2 }
    },
    { 
        "id": 4, 
        "product": "Tablet", 
        "price": 300, 
        "quantity": 3, 
        "date": { "year": 2024, "month": 2 }
    },
    { 
        "id": 5, 
        "product": "Phone", 
        "price": 500, 
        "quantity": 2, 
        "date": { "year": 2024, "month": 2 }
    }
])



db.sales.mapReduce(
    function() { 
        emit(this.date.year, this.quantity * this.price);  
    },
    function(key, values) { 
        return Array.sum(values);  
    }, 
    {
         
        out: "revenue_per_year",
        verbose:true
                             
    }
);

db.sales.mapReduce(
    function() {
        // Emit a composite key of year and month
        var yearMonth = this.date.year + "-" + this.date.month; // Format: "YYYY-MM"
        
        // Emit the composite key and an object with total revenue and transaction count
        emit(yearMonth, { totalRevenue: this.price * this.quantity, transactionCount: 1 });
    },
    function(key, values) {
        // Initialize the accumulator object for the year-month combination
        var result = { totalRevenue: 0, transactionCount: 0 };

        // Sum up the total revenue and count the transactions
        values.forEach(function(value) {
            result.totalRevenue += value.totalRevenue;
            result.transactionCount += value.transactionCount;
        });

        return result;
    },
    {
        out: "revenue_and_transactions_per_year_month",
        verbose: true
    }
);

// Check the output
db.revenue_and_transactions_per_year_month.find().pretty();

db.post_total.find()