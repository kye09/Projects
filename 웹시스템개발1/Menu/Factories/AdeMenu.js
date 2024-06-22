// CafeMenu를 상속 받아 에이드 메뉴를 생성하는 클래스
// createOrder 메서드에서 자몽에이드, 청포도에이드, 레몬에이드를 주문 패키지에 추가한다

import GrapefruitAde from '../Beverages/Ade/GrapefruitAde.js';
import GreenGrapeAde from '../Beverages/Ade/GreenGrapeAde.js';
import LemonAde from '../Beverages/Ade/LemonAde.js';
import CafeMenu from '../CafeMenu.js';

class AdeMenu extends CafeMenu {
    createOrder() {
        this.addPackage(new LemonAde());
        this.addPackage(new GreenGrapeAde());
        this.addPackage(new GrapefruitAde());
    }
}

export default AdeMenu;