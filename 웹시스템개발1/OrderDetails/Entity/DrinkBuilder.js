// Builder 패턴을 이용하여 주문 객체를 생성하는 클래스
// 메뉴 이름과 가격을 설정한 뒤, 주문 객체를 생성하여 반환한다
// 이 클래스를 이용하면 주문 객체를 유연하게 생성하고 관리할 수 있다

class DrinkBuilder {
    constructor() {
        this.order = {};
    }

    setMenuName(menuName) {
        this.order.menuName = menuName;
        return this;
    }

    setMenuPrice(menuPrice) {
        this.order.menuPrice = menuPrice;
        return this;
    }

    build() {
        return this.order;
    }
};

export default DrinkBuilder;