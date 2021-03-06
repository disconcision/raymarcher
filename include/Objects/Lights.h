//
// Created by disconcision on 21/03/19.
//

#ifndef RAYMARCHER_LIGHTS_H
#define RAYMARCHER_LIGHTS_H

#include "types.h"
#include <memory>


class Light {

public:
    Color I;
    bool castShadows;
    virtual ~Light() {};
    virtual void direction(
            const R3& p, // query point
            R3& d, //  p-to-light direction
            double& max_t // p-to-light distance
    ) const =0;
};


class DirectionalLight : public Light {

public:
    R3 d; // light-to-scene direction
    void direction(
            const R3& p,
            R3& d,
            R& max_d) const {
          // ignore query point
          d = - this->d.normalized();
          max_d = DBL_INFINITY;
    }
};


class PointLight : public Light {
public:
    R3 e; // light position
    void direction(
            const R3& p,
            R3& d,
            R& max_d) const {
      d = (this->e - p).normalized();
      max_d = (this->e - p).norm();
    }
};


struct Lights {

    std::vector<std::shared_ptr<Light>> data;

    void add_directional(R3 d, Color I, bool castShadows) {
      std::shared_ptr<DirectionalLight> l(new DirectionalLight());
      l->d = d;
      l->I = I;
      l->castShadows = castShadows;
      this->data.push_back(l);
    }

    void add_point(R3 e, Color I, bool castShadows) {
      std::shared_ptr<PointLight> l(new PointLight());
      l->e = e;
      l->I = I;
      l->castShadows = castShadows;
      this->data.push_back(l);
    }
};


#endif //RAYMARCHER_LIGHTS_H
