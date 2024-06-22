// CardPayment 클래스를 감싸고 있는 퍼사드 패턴을 구현한 클래스
// 카드 결제 과정을 한 번에 수행하는 processPayment 메서드를 제공한다


import CardPayment from './CardPayment.js';

class PaymentFacade {
    constructor() {
        this.cardPayment = new CardPayment();
    }

    processPayment() {
        this.cardPayment.insertCard();
        this.cardPayment.waitAndPrintPaymentStatus();
        this.cardPayment.ejectCard();
    }
}

export default PaymentFacade;