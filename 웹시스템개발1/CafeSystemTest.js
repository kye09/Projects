// 전체 카페 시스템의 흐름을 나타내는 테스트 코드
// 현재 코드상에선, 아메리카노를 주문한다고 가정한다.
// 주문을 하면 리스트에 적용이 되고, 카드로 결제를 하면 커피 제조가 된 뒤, 진동벨이 울리는 과정을 거친다.

import Americano from './Menu/Beverages/Coffee/Americano.js';
import OrderSystem from './OrderDetails/OrderSystem.js';

const customerName = '박범찬(고객)';

let orderSystem = new OrderSystem();
let americano = new Americano();

orderSystem.takeOrder(customerName, americano);

orderSystem.printOrders();