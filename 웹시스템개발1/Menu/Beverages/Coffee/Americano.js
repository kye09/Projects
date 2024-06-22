// Beverage를 상속 받아 아메리카노를 정의하는 클래스
// 아메리카노의 이름과 가격이 설정되어 있다
import Beverage from '../Beverage.js';

class Americano extends Beverage {
    constructor() {
        super();
        this.name = "아메리카노";
        this.price = 2.5;
    }
}

export default Americano;