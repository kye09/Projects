const express = require('express');
const router = express.Router();

const orderController = require('../controllers/order-controller');
const productController = require('../controllers/product-controller');

router.get('/search', productController.getByName);
router.post('/', orderController.createOrder);

module.exports = router;