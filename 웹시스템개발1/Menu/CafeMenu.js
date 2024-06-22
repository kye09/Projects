// 메뉴 패키지를 생성하고 관리하는 클래스
// 음료 객체를 포함하는 배열로, 새로운 음료 객체를 추가하거나 패키지 전체를 가져올 수 있다

class CafeMenu {
    constructor() {
        this.package = new Array();
    }
    createOrder() {}
    getPackage() {
        return this.package;
    }
    addPackage(object) {
        this.package.push(object);
    }
}

export default CafeMenu;
