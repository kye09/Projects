// Beverage를 상속 받아 자몽에이드를 정의하는 클래스
// 자몽에이드의 이름과 가격이 설정되어 있다
import Beverage from '../Beverage.js';

class GrapefruitAde extends Beverage {
    constructor() {
        super();
        this.name = "자몽에이드";
        this.price = 4.5;
    }
}

export default GrapefruitAde;