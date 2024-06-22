// 메뉴 폴더들 안의 파일을 불러와 정상적으로 잘 작동하는지 테스트하는 파일

import AdeMenu from './Factories/AdeMenu.js';
import CoffeeMenu from './Factories/CoffeeMenu.js';
import LatteMenu from './Factories/LatteMenu.js';

const customer1 = new CoffeeMenu();
customer1.createOrder();
console.log(customer1.getPackage());

const customer2 = new AdeMenu();
customer2.createOrder();
console.log(customer2.getPackage());

const customer3 = new LatteMenu();
customer3.createOrder();
console.log(customer3.getPackage());
