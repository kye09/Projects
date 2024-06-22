// 고객을 표현하는 클래스로 고객 이름과 주문을 가지고 있다
// 진동벨을 가지고 있어, 주문 음료가 제조 완료되었을 때 진동벨이 울린다
// 이 클래스는 Observer 패턴을 이용하여 음료 제조 완료를 통보받는다
// 여러 모듈과 상호작용하여 카페 주문과 음료 제조 과정을 구현한다

class Customer {
    constructor(name, order) {
        this.name = name;
        this.order = order;
    }

    update(drink) {
        if (drink.name === this.order.menuName) {
            console.log(`${this.name}: ${drink.name} 완성! 진동벨 울림.`);
        }
    }

    placeOrder(baristaAutomation) {
        baristaAutomation.addObserver(this);
        baristaAutomation.makeDrink(this.order);
    }
}

export default Customer;