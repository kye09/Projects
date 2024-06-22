// 음료를 만드는 자동화 시스템을 제어하며, observer 패턴을 통해 음료 제조 완료 시 알림을 주는 클래스
// 인스턴스를 사용하여 음료를 제조하고, 제조 완료 시 등록된 observer에게 알림을 준다

import BeverageMachine from './BeverageMachine.js';

class BaristaAutomation {
    constructor() {
        this.observers = [];
        this.beverageMachine = new BeverageMachine();
    }

    addObserver(observer) {
        this.observers.push(observer);
    }

    removeObserver(observer) {
        this.observers = this.observers.filter(obs => obs !== observer);
    }

    notifyObservers(drink) {
        this.observers.forEach(obs => obs.update(drink));
    }

    makeDrink(order) {
        console.log(`자동화 시스템: 주문하신 ${order.menuName} 제조를 시작합니다.`);
        this.beverageMachine.brewDrink(order.menuName).then(drink => {
            this.notifyObservers(drink); // 음료 제조가 완료된 후에 observer에게 알림
        });
    }
};

export default BaristaAutomation;
