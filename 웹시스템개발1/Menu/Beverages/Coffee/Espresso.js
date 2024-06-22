// Beverage를 상속 받아 에스프레소를 정의하는 클래스
// 에스프레소의 이름과 가격이 설정되어 있다
import Beverage from '../Beverage.js';

class Espresso extends Beverage {
    constructor() {
        super();
        this.name = "에스프레소";
        this.price = 2.5;
    }
}

export default Espresso;