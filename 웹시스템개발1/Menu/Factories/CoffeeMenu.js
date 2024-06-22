// CafeMenu를 상속 받아 커피 메뉴를 생성하는 클래스
// createOrder 메서드에서 아메리카노, 에스프레소, 콜드브루를 주문 패키지에 추가한다

import Americano from '../Beverages/Coffee/Americano.js';
import Coldbrew from '../Beverages/Coffee/Coldbrew.js';
import Espresso from '../Beverages/Coffee/Espresso.js';
import CafeMenu from '../CafeMenu.js';

class CoffeeMenu extends CafeMenu {
    createOrder() {
        this.addPackage(new Americano());
        this.addPackage(new Espresso());
        this.addPackage(new Coldbrew());
    }
}

export default CoffeeMenu;
