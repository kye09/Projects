// Beverage를 상속 받아 녹차라떼를 정의하는 클래스
// 녹차라떼의 이름과 가격이 설정되어 있다
import Beverage from '../Beverage.js';

class GreenTeaLatte extends Beverage {
    constructor() {
        super();
        this.name = "녹차라떼";
        this.price = 5.5;
    }
}

export default GreenTeaLatte;