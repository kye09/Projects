// CafeMenu를 상속 받아 라떼 메뉴를 생성하는 클래스
// createOrder 메서드에서 달고나라떼, 녹차라떼, 바닐라라뗴를 주문 패키지에 추가한다

import DalgonaLatte from '../Beverages/Latte/DalgonaLatte.js';
import GreenTeaLatte from '../Beverages/Latte/GreenTeaLatte.js';
import VanillaLatte from '../Beverages/Latte/VanillaLatte.js';
import CafeMenu from '../CafeMenu.js';

class LatteMenu extends CafeMenu {
    createOrder() {
        this.addPackage(new DalgonaLatte());
        this.addPackage(new GreenTeaLatte());
        this.addPackage(new VanillaLatte());
    }
}

export default LatteMenu;