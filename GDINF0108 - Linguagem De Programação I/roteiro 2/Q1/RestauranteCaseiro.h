#ifndef RESTAURANTECASEIRO_H
#define RESTAURANTECASEIRO_H

#define QNT_MESAS 10
#include "MesaDeRestaurante.cpp"

class RestauranteCaseiro{
    MesaDeRestaurante mesas[QNT_MESAS] = {};

    public:
        void adicionaPedido(Pedido, int);
        double calculaTotalRestaurante();
};

#endif // RESTAURANTECASEIRO_H
