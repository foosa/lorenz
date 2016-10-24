/*
 * -*- coding: utf-8 -*-
 *
 * Program:     lorenz
 * Author:      True Merrill
 * Date:        Oct 23 2016
 *
 */

#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>


struct lorenz_parameters {
    double sigma;
    double rho;
    double beta;
};


/**
 * @brief RHS of the lorenz attractor system
 *
 * @param t
 * @param y[]
 * @param f[]
 * @param params
 *
 * @return 
 */
int lorenz_attractor (double t, const double y[], double f[], void *params) {
    struct lorenz_parameters *p;
    p = (struct lorenz_parameters *) params;
    f[0] = p->sigma * (y[1] - y[0]);
    f[1] = y[0] * (p->rho - y[2]) - y[1];
    f[2] = y[0] * y[1] - p->beta * y[2];
    return GSL_SUCCESS;
}


int main (void) {
    struct lorenz_parameters param = {10, 28, 8/3};
    gsl_odeiv2_system sys = {lorenz_attractor, NULL, 3, &param};
    gsl_odeiv2_driver *d = gsl_odeiv2_driver_alloc_y_new (&sys,
            gsl_odeiv2_step_rk4, 1e-6, 1e-6, 0.0);

    int num_steps = 1e4;
    double t0 = 0.0;
    double t1 = 5e1;
    double t = t0;
    double dt = (t1 - t0) / num_steps;

    // Initial state
    double y[3] = {1, 1, 1};

    while (t < t1) {
        int status = gsl_odeiv2_driver_apply (d, &t, t + dt, y);

        if (status != GSL_SUCCESS) {
            printf ("error, return value = %d\n", status);
            break;
        }

        printf ("%e % .6e % .6e % .6e\n", t, y[0], y[1], y[2]);
        //t += dt;
    }

    gsl_odeiv2_driver_free (d);
    return 0;
}
