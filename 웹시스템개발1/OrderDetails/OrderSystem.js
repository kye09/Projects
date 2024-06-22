// 주문 시스템을 관리하는 핵심 클래스로 현재 주문 리스트를 출력하는 기능을 제공한다
// 주문을 받아 처리하고, 결제를 진행한 뒤, 바리스타 자동화 시스템에게 음료 제조를 요청한다.


import BaristaAutomation from '../CoffeeMachine/BaristaAutomation.js';
import Customer from '../Customer.js';
import PaymentFacade from '../PaymentSystem/CardPaymentFacade.js';
import { createOrder, getOrders } from './OrderModule.js';

class OrderSystem {
    constructor() {
        this.baristaAutomation = new BaristaAutomation();
        this.paymentFacade = new PaymentFacade();
    }

    takeOrder(customerName, menu) {
        createOrder(menu);
        const order = getOrders()[getOrders().length - 1];
        const customer = new Customer(customerName, order);

        this.processPayment().then(() => {
            customer.placeOrder(this.baristaAutomation);
        });
    }

    printOrders() {
        const orders = getOrders();
        console.log("\n현재 주문 리스트: \n", orders);
    }

    processPayment() {
        // PaymentFacade의 processPayment() 메서드가 Promise를 반환하도록 변경
        return new Promise((resolve) => {
            this.paymentFacade.processPayment();
            setTimeout(resolve, 3000);
        });
    }
}

export default OrderSystem;