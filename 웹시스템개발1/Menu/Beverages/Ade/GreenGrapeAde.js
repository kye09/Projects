// Beverage를 상속 받아 청포도에이드를 정의하는 클래스
// 청포도에이드의 이름과 가격이 설정되어 있다
import Beverage from '../Beverage.js';

class GreenGrapeAde extends Beverage {
    constructor() {
        super();
        this.name = "청포도에이드";
        this.price = 4.5;
    }
}

export default GreenGrapeAde;