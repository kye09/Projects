// Beverage를 상속 받아 레몬에이드를 정의하는 클래스
// 레몬에이드의 이름과 가격이 설정되어 있다
import Beverage from '../Beverage.js';

class LemonAde extends Beverage {
    constructor() {
        super();
        this.name = "레몬에이드";
        this.price = 4.5;
    }
}

export default LemonAde;