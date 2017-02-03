/*
 * =====================================================================================
 *
 *       Filename:  fwi_kernel.h
 *
 *    Description:  Kernel propagator implementation
 *
 *        Version:  1.0
 *        Created:  14/12/15 12:10:24
 *       Revision:  none
 *       Compiler:  icc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */
#pragma once

#include "fwi_propagator.h"
#include "fwi_comms.h"

/*
 * Ensures that the domain contains a minimum number of planes.
 * Just needed for debugging when running small cases.
 */
void check_domain_dimensions ( const integer dimmz,
                               const integer dimmx,
                               const integer dimmy);

void set_array_to_random_real(real* restrict array,
                              const integer length);

void set_array_to_constant(real* restrict array,
                           const real value,
                           const integer length);

void alloc_memory_shot( const integer dimmz,
		const integer dimmx,
		const integer dimmy,
                        coeff_t *c,
                        s_t     *s,
                        v_t     *v,
                        real    **rho);

void free_memory_shot( coeff_t *c,
                       s_t     *s,
                       v_t     *v,
                       real    **rho);

void check_memory_shot( const integer dimmz,
		const integer dimmx,
		const integer dimmy,
                        coeff_t *c,
                        s_t     *s,
                        v_t     *v,
                        real    *rho);

/* --------------- I/O RELATED FUNCTIONS -------------------------------------- */
void load_local_velocity_model ( const real    waveletFreq,
													const integer dimmz,
													const integer dimmx,
													const integer dimmy,
                          coeff_t *c,
                          s_t     *s,
                          v_t     *v,
                          real    *rho);

void write_snapshot ( char          *folder,
                      const int     suffix,
                      v_t          *v,
                      const integer dimmz,
											const integer dimmx,
											const integer dimmy);

void read_snapshot ( char          *folder,
                     const int     suffix,
                     v_t          *v,
                     const integer dimmz,
										 const integer dimmx,
										 const integer dimmy);



/* --------------- WAVE PROPAGATOR FUNCTIONS --------------------------------- */

void propagate_shot ( time_d        direction,
                     v_t           v,
                     s_t           s,
                     coeff_t       coeffs,
                     real          *rho,
                     int           timesteps,
                     int           ntbwd,
                     real          dt,
                     real          dzi,
                     real          dxi,
                     real          dyi,
                     integer       nz0,
                     integer       nzf,
                     integer       nx0,
                     integer       nxf,
                     integer       ny0,
                     integer       nyf,
                     integer       stacki,
                     char          *folder,
                     real          *UNUSED(dataflush),
                     integer       dimmz,
                     integer       dimmx,
                     integer       dimmy);
