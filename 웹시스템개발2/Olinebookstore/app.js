const express = require('express');
const morgan = require('morgan');
var winston = require('./config/winston');
const app = express();
const bodyParser = require('body-parser');

const productRoutes = require('./routes/products-routes');
const orderRoutes = require('./routes/orders-routes');
const userRouters = require('./routes/user');
 
app.use((req, res, next) => {
    res.header("Access-Control-Allow-Origin", '*');
    res.header(
        "Access-Control-Allow-Headers",
        "Origin, X-Requested-With, Content-Type, Accept, Authorization"
    );
    if (req.method === 'OPTIONS') {
        res.header('Access-Control-Allow-Methods', 'PUT, POST, PATCH, DELETE, GET');
        return res.status(200).json({});
    } else {
        next();
    }
});

app.get('/', (req, res) => {
    res.send('온라인서점입니다!');
  });

// Logger configuration
app.use(morgan('combined', { stream: winston.stream }));

// Express configuration
app.use(express.json());
app.use(express.urlencoded({ extended: false }));

// app.use(bodyParser());

// Routes

app.use('/products', productRoutes);
app.use('/orders', orderRoutes);
app.use('/user', userRouters);

app.listen(3000);
console.log('Server init at port ' + 3000);

module.exports = app;