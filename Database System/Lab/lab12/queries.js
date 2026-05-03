/* 
   Q1 (A & B): LibraryDB and Books Collection
*/

use LibraryDB;


db.Books.insertMany([
    { title: "The Martian", author: "Andy Weir", year: 2011 },
    { title: "Atomic Habits", author: "James Clear", year: 2018 },
    { title: "Dune", author: "Frank Herbert", year: 1965 }
]);

db.Books.find();
db.Books.find({ year: { $gt: 2015 } });


/* 
   Q2 (A): Find Users based on Age & Subscription
*/
//  dummy data 
db.users.insertMany([
    { name: "Alice", age: 26, city: "NY", subscriptionType: "Premium" },
    { name: "Bob", age: 24, city: "LA", subscriptionType: "Premium" },
    { name: "Charlie", age: 30, city: "SF", subscriptionType: "Basic" }
]);


db.users.find({ 
    age: { $gt: 25 }, 
    subscriptionType: "Premium" 
});


/*
   Q2 (B): Find Orders based on Amount OR Status
*/

db.orders.find({
    $or: [
        { totalAmount: { $gt: 5000 } },
        { status: "Pending" }
    ]
});


/*
   Q3 (A): Bookstore Data Tasks
*/
db.bookstore.countDocuments({ sales: { $gt: 1000 } });

db.bookstore.find().sort({ sales: -1 }).limit(3);


/* 
   Q3 (B): Blogging Platform Posts
 */

db.posts.find({
    likes: { $gt: 100 },
    tags: "tech", 
    $expr: { $gt: [{ $size: "$comments" }, 2] } 
});


/* 
   Q4: Ride-hailing App (Aggregation)
*/
db.trips.insertMany([
    { driverId: 1, city: "Karachi", fare: 30000, status: "completed" },
    { driverId: 2, city: "Karachi", fare: 25000, status: "completed" },
    { driverId: 3, city: "Lahore", fare: 15000, status: "completed" }
]);

db.trips.aggregate([
    { 
        $group: { 
            _id: "$city", 
            totalRevenue: { $sum: "$fare" } 
        } 
    },
    { 
        $match: { 
            totalRevenue: { $gt: 50000 } 
        } 
    },
    { 
        $sort: { totalRevenue: -1 } 
    }
]);


/* 
   Q5: Online Store Mixed Operations
 */
db.products.find({ 
    price: { $lt: 1000 }, 
    stock: { $gt: 0 } 
});

db.products.updateMany(
    { category: "Electronics" },
    { $inc: { stock: -5 } } 
);

db.products.aggregate([
    { 
        $group: { 
            _id: "$category", 
            productCount: { $sum: 1 } 
        } 
    }
]);

db.products.createIndex({ productName: "text" });

db.products.find({ 
    $text: { $search: "laptop" } 
});
