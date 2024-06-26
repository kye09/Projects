'use strict';

module.exports = {
    up: (queryInterface, Sequelize) => {
        return queryInterface.bulkInsert('Products', [{
            name: '웹시스템개발',
            price: 10
        },
        {
            name: '네트워크프로그래밍',
            price: 20
        },
        {
            name: '데이터마이닝과통계',
            price: 30
        },
        {
            name: '이미지딥러닝',
            price: 40
        }], {});
    },

    down: (queryInterface, Sequelize) => {
        return queryInterface.bulkDelete('Products', null, {});
    }
};
