// 주문을 생성하고, 주문 리스트를 관리하는 모듈로 주문 리스트를 가져오는 기능을 포함함
// DrinkBuilder 클래스를 사용하여 주문을 생성하고, 이를 주문 리스트에 추가한다

import DrinkBuilder from './Entity/DrinkBuilder.js';

let orders = [];

function createOrder(menu) {
    let drinkBuilder = new DrinkBuilder();
    drinkBuilder.setMenuName(menu.name);
    drinkBuilder.setMenuPrice(menu.price);
    let order = drinkBuilder.build();
    orders.push(order);
}

function getOrders() {
    return orders;
}

export { createOrder, getOrders };
