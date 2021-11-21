//
// Created by leodlplq on 16/11/2021.
//

#include "Triangle.h"

Triangle::Triangle() :
    t_VertexCount(0)
{
   build();
}

void Triangle::build() {
    t_Vertices = {-0.5f, -0.5f, 0.f,
                  0.5f, -0.5f, 0.f,
                  0.0f, 0.5f, 0.f};
    t_VertexCount = 9;
}

