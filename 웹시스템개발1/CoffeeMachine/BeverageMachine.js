// 음료를 제조하는 로직을 포함하는 클래스
// 각 음료는 3초의 제조 시간을 가정하며, 제조 완료 시 Promise가 resolve되어 제조 완료가 알려진다

class BeverageMachine {
    brewDrink(drinkName) {
        return new Promise((resolve) => {
            console.log(`음료기계: ${drinkName} 제조 시작...`);
            setTimeout(() => {
                console.log(`음료기계: ${drinkName} 완성!`);
                resolve({ name: drinkName });
            }, 3000);
        });
    }
};

export default BeverageMachine;
