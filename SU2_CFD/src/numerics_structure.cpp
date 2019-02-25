﻿/*!
 * \file numerics_structure.cpp
 * \brief This file contains all the numerical methods.
 * \author F. Palacios, T. Economon
 * \version 6.1.0 "Falcon"
 *
 * The current SU2 release has been coordinated by the
 * SU2 International Developers Society <www.su2devsociety.org>
 * with selected contributions from the open-source community.
 *
 * The main research teams contributing to the current release are:
 *  - Prof. Juan J. Alonso's group at Stanford University.
 *  - Prof. Piero Colonna's group at Delft University of Technology.
 *  - Prof. Nicolas R. Gauger's group at Kaiserslautern University of Technology.
 *  - Prof. Alberto Guardone's group at Polytechnic University of Milan.
 *  - Prof. Rafael Palacios' group at Imperial College London.
 *  - Prof. Vincent Terrapon's group at the University of Liege.
 *  - Prof. Edwin van der Weide's group at the University of Twente.
 *  - Lab. of New Concepts in Aeronautics at Tech. Institute of Aeronautics.
 *
 * Copyright 2012-2018, Francisco D. Palacios, Thomas D. Economon,
 *                      Tim Albring, and the SU2 contributors.
 *
 * SU2 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * SU2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with SU2. If not, see <http://www.gnu.org/licenses/>.
 */

#include "../include/numerics_structure.hpp"

CNumerics::CNumerics(void) {

  Normal      = NULL;
  UnitNormal  = NULL;
  UnitNormald = NULL;
  
  U_n   = NULL;
  U_nM1 = NULL;
  U_nP1 = NULL;
 
  Proj_Flux_Tensor  = NULL;
  Flux_Tensor       = NULL;
 
  tau    = NULL;
  delta  = NULL;
  delta3 = NULL;

  Diffusion_Coeff_i = NULL;
  Diffusion_Coeff_j = NULL;

  Enthalpy_formation = NULL;
  Theta_v = NULL;

  l = NULL;
  m = NULL;

}

CNumerics::CNumerics(unsigned short val_nDim, unsigned short val_nVar,
                     CConfig *config) {
  
  unsigned short iVar, iDim, jDim;
  
  Normal      = NULL;
  UnitNormal  = NULL;
  UnitNormald = NULL;
  
  U_n   = NULL;
  U_nM1 = NULL;
  U_nP1 = NULL;
  
  Proj_Flux_Tensor  = NULL;
  Flux_Tensor       = NULL;
  
  tau    = NULL;
  delta  = NULL;
  delta3 = NULL;

  Diffusion_Coeff_i = NULL;
  Diffusion_Coeff_j = NULL;

  Enthalpy_formation = NULL;
  Theta_v = NULL;

  l = NULL;
  m = NULL;

  MeanReynoldsStress  = NULL; 
  MeanPerturbedRSM    = NULL;
  A_ij                = NULL;
  Eig_Vec             = NULL;
  New_Eig_Vec         = NULL;
  newA_ij             = NULL;
  Corners             = NULL;
  Eig_Val             = NULL;
  Barycentric_Coord   = NULL;
  New_Coord           = NULL;    
 
  nDim = val_nDim;
  nVar = val_nVar;
  Gamma = config->GetGamma();
  Gamma_Minus_One = Gamma - 1.0;
  Prandtl_Lam = config->GetPrandtl_Lam();
  Prandtl_Turb = config->GetPrandtl_Turb();
  Gas_Constant = config->GetGas_ConstantND();

  UnitNormal = new su2double [nDim];
  UnitNormald = new su2double [nDim];

  Flux_Tensor = new su2double* [nVar];
  for (iVar = 0; iVar < (nVar); iVar++)
    Flux_Tensor[iVar] = new su2double [nDim];

  tau = new su2double* [nDim];
  for (iDim = 0; iDim < nDim; iDim++) {
    tau[iDim] = new su2double [nDim];
  }

  delta = new su2double* [nDim];
  for (iDim = 0; iDim < nDim; iDim++) {
    delta[iDim] = new su2double [nDim];
  }

  for (iDim = 0; iDim < nDim; iDim++) {
    for (jDim = 0; jDim < nDim; jDim++) {
      if (iDim == jDim) delta[iDim][jDim] = 1.0;
      else delta[iDim][jDim]=0.0;
    }
  }

  delta3 = new su2double* [3];
  for (iDim = 0; iDim < 3; iDim++) {
    delta3[iDim] = new su2double [3];
  }

  for (iDim = 0; iDim < 3; iDim++) {
    for (jDim = 0; jDim < 3; jDim++) {
      if (iDim == jDim) delta3[iDim][jDim] = 1.0;
      else delta3[iDim][jDim]=0.0;
    }
  }

  U_n   = new su2double [nVar];
  U_nM1 = new su2double [nVar];
  U_nP1 = new su2double [nVar];

  Proj_Flux_Tensor = new su2double [nVar];

  turb_ke_i = 0.0;
  turb_ke_j = 0.0;
  
  Vector = new su2double[nDim];
  
  l = new su2double [nDim];
  m = new su2double [nDim];
  
  Dissipation_ij = 1.0;

  /*--- Initializing variables for TNE ---*/
  Diffusion_Coeff_i = NULL;  Diffusion_Coeff_j = NULL;

  hs     = NULL; Cvtr   = NULL;
  eve_i  = NULL; eve_j  = NULL;
  Cvve_i = NULL; Cvve_j = NULL;
  Ys_i   = NULL; Ys_j   = NULL;
  In     = NULL;
  dYdr_i = NULL; dYdr_j = NULL;
  dIdr_i = NULL; dIdr_j = NULL;
  dJdr_i = NULL; dJdr_j = NULL;

  Ys          = NULL;
  dFdVi       = NULL;  dFdVj       = NULL;
  dFdYj       = NULL;  dFdYi       = NULL;
  dVdUi       = NULL;  dVdUj       = NULL;
  sumdFdYih   = NULL;  sumdFdYjh   = NULL;
  sumdFdYieve = NULL;  sumdFdYjeve = NULL;

  if ((config->GetKind_Solver() == TNE2_EULER)                 ||
      (config->GetKind_Solver() == TNE2_NAVIER_STOKES)         ||
      (config->GetKind_Solver() == DISC_ADJ_TNE2_EULER)        ||
      (config->GetKind_Solver() == DISC_ADJ_TNE2_NAVIER_STOKES) ) {
    nSpecies = nVar - nDim - 2;

    hs     = new su2double[nSpecies];
    Cvtr   = new su2double[nSpecies];
    eve_i  = new su2double[nSpecies];  eve_j  = new su2double[nSpecies];
    Cvve_i = new su2double[nSpecies];  Cvve_j = new su2double[nSpecies];
    Ys_i   = new su2double[nSpecies];  Ys_j   = new su2double[nSpecies];
    In     = new su2double[nSpecies];
    dYdr_i = new su2double*[nSpecies]; dYdr_j = new su2double*[nSpecies];
    dIdr_i = new su2double*[nSpecies]; dIdr_j = new su2double*[nSpecies];
    dJdr_i = new su2double*[nSpecies]; dJdr_j = new su2double*[nSpecies];

    for (unsigned short iSpecies = 0; iSpecies < nSpecies; iSpecies++) {
      dYdr_i[iSpecies] = new su2double[nSpecies];
      dYdr_j[iSpecies] = new su2double[nSpecies];
      dIdr_i[iSpecies] = new su2double[nSpecies];
      dIdr_j[iSpecies] = new su2double[nSpecies];
      dJdr_i[iSpecies] = new su2double[nSpecies];
      dJdr_j[iSpecies] = new su2double[nSpecies];
    }
    dFdVi = new su2double*[nVar];
    dFdVj = new su2double*[nVar];
    dVdUi = new su2double*[nVar];
    dVdUj = new su2double*[nVar];
    for (unsigned short iVar = 0; iVar < nVar; iVar++) {
      dFdVi[iVar] = new su2double[nVar];
      dFdVj[iVar] = new su2double[nVar];
      dVdUi[iVar] = new su2double[nVar];
      dVdUj[iVar] = new su2double[nVar];
    }

    Ys = new su2double[nSpecies];
    dFdYi = new su2double *[nSpecies];
    dFdYj = new su2double *[nSpecies];
    for (unsigned short iSpecies = 0; iSpecies < nSpecies; iSpecies++) {
      dFdYi[iSpecies] = new su2double[nSpecies];
      dFdYj[iSpecies] = new su2double[nSpecies];
    }
    sumdFdYih   = new su2double[nSpecies];
    sumdFdYjh   = new su2double[nSpecies];
    sumdFdYieve = new su2double[nSpecies];
    sumdFdYjeve = new su2double[nSpecies];

    Diffusion_Coeff_i = new su2double[nSpecies];
    Diffusion_Coeff_j = new su2double[nSpecies];
    unsigned short nPrimVar     = nSpecies+nDim+8;
    unsigned short nPrimVarGrad = nSpecies+nDim+8;
    var = new CTNE2EulerVariable(nDim, nVar, nPrimVar, nPrimVarGrad, config);
  }

  /* --- Initializing variables for the UQ methodology --- */
  using_uq = config->GetUsing_UQ();
  if (using_uq){
    MeanReynoldsStress  = new su2double* [3];
    MeanPerturbedRSM    = new su2double* [3];
    A_ij                = new su2double* [3];          
    newA_ij             = new su2double* [3];
    Eig_Vec             = new su2double* [3];
    New_Eig_Vec         = new su2double* [3];
    Corners             = new su2double* [3];
    Eig_Val             = new su2double [3];
    Barycentric_Coord   = new su2double [2];
    New_Coord           = new su2double [2];
    for (iDim = 0; iDim < 3; iDim++){
      MeanReynoldsStress[iDim]  = new su2double [3];
      MeanPerturbedRSM[iDim]    = new su2double [3];
      A_ij[iDim]                = new su2double [3];
      newA_ij[iDim]             = new su2double [3];
      Eig_Vec[iDim]             = new su2double [3];
      New_Eig_Vec[iDim]         = new su2double [3];
      Corners[iDim]             = new su2double [2];
      Eig_Val[iDim]             = 0;
    }
    Eig_Val_Comp = config->GetEig_Val_Comp();
    uq_delta_b = config->GetUQ_Delta_B();
    uq_urlx = config->GetUQ_URLX();
    uq_permute = config->GetUQ_Permute();

    /* define barycentric traingle corner points */
    Corners[0][0] = 1.0;
    Corners[0][1] = 0.0;
    Corners[1][0] = 0.0;
    Corners[1][1] = 0.0;
    Corners[2][0] = 0.5;
    Corners[2][1] = 0.866025;
  }
  
}

CNumerics::~CNumerics(void) {

  unsigned short iDim, iSpecies, iVar;

  if (UnitNormal!= NULL) delete [] UnitNormal;
  if (UnitNormald!= NULL) delete [] UnitNormald;

  if (U_n!= NULL) delete [] U_n;
  if (U_nM1!= NULL) delete [] U_nM1;
  if (U_nP1!= NULL) delete [] U_nP1;

  // visc
  if (Proj_Flux_Tensor!= NULL) delete [] Proj_Flux_Tensor;

  if (Flux_Tensor!= NULL) {
    for (unsigned short iVar = 0; iVar < nVar; iVar++) {
      delete [] Flux_Tensor[iVar];
    }
    delete [] Flux_Tensor;
  }

  if (tau != NULL) {
    for (unsigned short iDim = 0; iDim < nDim; iDim++) {
      delete [] tau[iDim];
    }
    delete [] tau;
  }

  if (delta != NULL) {
    for (unsigned short iDim = 0; iDim < nDim; iDim++) {
      delete [] delta[iDim];
    }
    delete [] delta;
  }

  if (delta3 != NULL) {
    for (unsigned short iDim = 0; iDim < 3; iDim++) {
      delete [] delta3[iDim];
    }
    delete [] delta3;
  }

  if (Diffusion_Coeff_i != NULL) delete [] Diffusion_Coeff_i;
  if (Diffusion_Coeff_j != NULL) delete [] Diffusion_Coeff_j;
  if (Vector != NULL) delete [] Vector;

  if(Enthalpy_formation != NULL) delete [] Enthalpy_formation;
  if(Theta_v != NULL) delete [] Theta_v;

  if (l != NULL) delete [] l;
  if (m != NULL) delete [] m;

  if (hs     != NULL) delete [] hs;
  if (Cvtr   != NULL) delete [] Cvtr;
  //if (eve_i  != NULL) delete [] eve_i;
  //if (eve_j  != NULL) delete [] eve_j;
  //if (Cvve_i != NULL) delete [] Cvve_i;
  //if (Cvve_j != NULL) delete [] Cvve_j; These cause seg faults?
  if (Ys_i   != NULL) delete [] Ys_i;
  if (Ys_j   != NULL) delete [] Ys_j;
  if (In     != NULL) delete [] In;

  if (dYdr_i != NULL) {
    for (iSpecies = 0; iSpecies < nSpecies; iSpecies++)
      delete [] dYdr_i[iSpecies];
    delete [] dYdr_i;
  }
  if (dYdr_j != NULL) {
    for (iSpecies = 0; iSpecies < nSpecies; iSpecies++)
      delete [] dYdr_j[iSpecies];
    delete [] dYdr_j;
  }
  if (dIdr_i != NULL) {
    for (iSpecies = 0; iSpecies < nSpecies; iSpecies++)
      delete [] dIdr_i[iSpecies];
    delete [] dIdr_i;
  }
  if (dIdr_j != NULL) {
    for (iSpecies = 0; iSpecies < nSpecies; iSpecies++)
      delete [] dIdr_j[iSpecies];
    delete [] dIdr_j;
  }
  if (dJdr_i != NULL) {
    for (iSpecies = 0; iSpecies < nSpecies; iSpecies++)
      delete [] dJdr_i[iSpecies];
    delete [] dJdr_i;
  }
  if (dJdr_j != NULL) {
    for (iSpecies = 0; iSpecies < nSpecies; iSpecies++)
      delete [] dJdr_j[iSpecies];
    delete [] dJdr_j;
  }
  if (dFdVi != NULL) {
    for (iVar = 0; iVar < nVar; iVar++)
      delete [] dFdVi[iVar];
    delete [] dFdVi;
  }
  if (dFdVj != NULL) {
    for (iVar = 0; iVar < nVar; iVar++)
      delete [] dFdVj[iVar];
    delete [] dFdVj;
  }
  if (dVdUi != NULL) {
    for (iVar = 0; iVar < nVar; iVar++)
      delete [] dVdUi[iVar];
    delete [] dVdUi;
  }
  if (dVdUj != NULL) {
    for (iVar = 0; iVar < nVar; iVar++)
      delete [] dVdUj[iVar];
    delete [] dVdUj;
  }

  if (Ys != NULL) delete [] Ys;
  if (dFdYi != NULL) {
    for (unsigned short iSpecies = 0; iSpecies < nSpecies; iSpecies++)
      delete [] dFdYi[iSpecies];
    delete [] dFdYi;
  }
  if (dFdYj != NULL) {
    for (unsigned short iSpecies = 0; iSpecies < nSpecies; iSpecies++)
      delete [] dFdYj[iSpecies];
    delete [] dFdYj;
  }
  if (sumdFdYih != NULL) delete [] sumdFdYih;
  if (sumdFdYjh != NULL) delete [] sumdFdYjh;
  if (sumdFdYieve != NULL) delete [] sumdFdYieve;
  if (sumdFdYjeve != NULL) delete [] sumdFdYjeve;

  if (using_uq) {
    for (unsigned short iDim = 0; iDim < 3; iDim++){
      delete [] MeanReynoldsStress[iDim];
      delete [] MeanPerturbedRSM[iDim];
      delete [] A_ij[iDim];
      delete [] newA_ij[iDim];
      delete [] Eig_Vec[iDim];
      delete [] New_Eig_Vec[iDim];
      delete [] Corners[iDim];
    }
    delete [] MeanReynoldsStress;
    delete [] MeanPerturbedRSM;
    delete [] A_ij;
    delete [] newA_ij;
    delete [] Eig_Vec;
    delete [] New_Eig_Vec;
    delete [] Corners;
    delete [] Eig_Val;
    delete [] Barycentric_Coord;
    delete [] New_Coord;
  }

}

void CNumerics::GetInviscidFlux(su2double val_density, su2double *val_velocity,
    su2double val_pressure, su2double val_enthalpy) {
  if (nDim == 3) {
    Flux_Tensor[0][0] = val_density*val_velocity[0];
    Flux_Tensor[1][0] = Flux_Tensor[0][0]*val_velocity[0]+val_pressure;
    Flux_Tensor[2][0] = Flux_Tensor[0][0]*val_velocity[1];
    Flux_Tensor[3][0] = Flux_Tensor[0][0]*val_velocity[2];
    Flux_Tensor[4][0] = Flux_Tensor[0][0]*val_enthalpy;

    Flux_Tensor[0][1] = val_density*val_velocity[1];
    Flux_Tensor[1][1] = Flux_Tensor[0][1]*val_velocity[0];
    Flux_Tensor[2][1] = Flux_Tensor[0][1]*val_velocity[1]+val_pressure;
    Flux_Tensor[3][1] = Flux_Tensor[0][1]*val_velocity[2];
    Flux_Tensor[4][1] = Flux_Tensor[0][1]*val_enthalpy;

    Flux_Tensor[0][2] = val_density*val_velocity[2];
    Flux_Tensor[1][2] = Flux_Tensor[0][2]*val_velocity[0];
    Flux_Tensor[2][2] = Flux_Tensor[0][2]*val_velocity[1];
    Flux_Tensor[3][2] = Flux_Tensor[0][2]*val_velocity[2]+val_pressure;
    Flux_Tensor[4][2] = Flux_Tensor[0][2]*val_enthalpy;

  }
  if (nDim == 2) {
    Flux_Tensor[0][0] = val_density*val_velocity[0];
    Flux_Tensor[1][0] = Flux_Tensor[0][0]*val_velocity[0]+val_pressure;
    Flux_Tensor[2][0] = Flux_Tensor[0][0]*val_velocity[1];
    Flux_Tensor[3][0] = Flux_Tensor[0][0]*val_enthalpy;

    Flux_Tensor[0][1] = val_density*val_velocity[1];
    Flux_Tensor[1][1] = Flux_Tensor[0][1]*val_velocity[0];
    Flux_Tensor[2][1] = Flux_Tensor[0][1]*val_velocity[1]+val_pressure;
    Flux_Tensor[3][1] = Flux_Tensor[0][1]*val_enthalpy;
  }
}

void CNumerics::GetInviscidProjFlux(su2double *val_density,
                                    su2double *val_velocity,
                                    su2double *val_pressure,
                                    su2double *val_enthalpy,
                                    su2double *val_normal,
                                    su2double *val_Proj_Flux) {
  
    su2double rhou, rhov, rhow;
    
  if (nDim == 2) {
    
    rhou = (*val_density)*val_velocity[0];
    rhov = (*val_density)*val_velocity[1];

    val_Proj_Flux[0] = rhou*val_normal[0];
    val_Proj_Flux[1] = (rhou*val_velocity[0]+(*val_pressure))*val_normal[0];
    val_Proj_Flux[2] = rhou*val_velocity[1]*val_normal[0];
    val_Proj_Flux[3] = rhou*(*val_enthalpy)*val_normal[0];

    val_Proj_Flux[0] += rhov*val_normal[1];
    val_Proj_Flux[1] += rhov*val_velocity[0]*val_normal[1];
    val_Proj_Flux[2] += (rhov*val_velocity[1]+(*val_pressure))*val_normal[1];
    val_Proj_Flux[3] += rhov*(*val_enthalpy)*val_normal[1];
    
  } 
  else {
    
    rhou = (*val_density)*val_velocity[0];
    rhov = (*val_density)*val_velocity[1];
    rhow = (*val_density)*val_velocity[2];

    val_Proj_Flux[0] = rhou*val_normal[0];
    val_Proj_Flux[1] = (rhou*val_velocity[0]+(*val_pressure))*val_normal[0];
    val_Proj_Flux[2] = rhou*val_velocity[1]*val_normal[0];
    val_Proj_Flux[3] = rhou*val_velocity[2]*val_normal[0];
    val_Proj_Flux[4] = rhou*(*val_enthalpy)*val_normal[0];

    val_Proj_Flux[0] += rhov*val_normal[1];
    val_Proj_Flux[1] += rhov*val_velocity[0]*val_normal[1];
    val_Proj_Flux[2] += (rhov*val_velocity[1]+(*val_pressure))*val_normal[1];
    val_Proj_Flux[3] += rhov*val_velocity[2]*val_normal[1];
    val_Proj_Flux[4] += rhov*(*val_enthalpy)*val_normal[1];

    val_Proj_Flux[0] += rhow*val_normal[2];
    val_Proj_Flux[1] += rhow*val_velocity[0]*val_normal[2];
    val_Proj_Flux[2] += rhow*val_velocity[1]*val_normal[2];
    val_Proj_Flux[3] += (rhow*val_velocity[2]+(*val_pressure))*val_normal[2];
    val_Proj_Flux[4] += rhow*(*val_enthalpy)*val_normal[2];
    
  }

}

void CNumerics::GetInviscidProjFlux(su2double *val_U,
                                    su2double *val_V,
                                    su2double *val_normal,
                                    su2double *val_Proj_Flux) {
  unsigned short iSpecies, iVar;
  su2double rho, u, v, w, rhoEve, P, H;
  su2double *rhos;

  /*--- Allocate arrays ---*/
  rhos = new su2double[nSpecies];

  /*--- Initialize vectors ---*/
  for (iVar = 0; iVar < nVar; iVar++)
    val_Proj_Flux[iVar] = 0.0;

  /*--- Rename for convienience ---*/
  rho    = val_V[RHO_INDEX];
  u      = val_V[VEL_INDEX];
  v      = val_V[VEL_INDEX+1];
  w      = val_V[VEL_INDEX+2];
  P      = val_V[P_INDEX];
  H      = val_V[H_INDEX];
  rhoEve = val_U[nSpecies+nDim+1];
  for (iSpecies = 0; iSpecies < nSpecies; iSpecies++) {
    rhos[iSpecies] = val_V[RHOS_INDEX+iSpecies];
  }

  if (nDim == 2) {

    /*--- iDim = 0 (x-direction) ---*/
    for (iSpecies = 0; iSpecies < nSpecies; iSpecies++)
      val_Proj_Flux[iSpecies]  = (rhos[iSpecies]*u) * val_normal[0];
		val_Proj_Flux[nSpecies]    = (rho*u*u + P)      * val_normal[0];
		val_Proj_Flux[nSpecies+1]  = (rho*u*v)          * val_normal[0];
		val_Proj_Flux[nSpecies+2]  = (rho*u*H)          * val_normal[0];
    val_Proj_Flux[nSpecies+3]  = (rhoEve*u)         * val_normal[0];

    /*---- iDim = 1 (y-direction) ---*/
    for (iSpecies = 0; iSpecies < nSpecies; iSpecies++)
      val_Proj_Flux[iSpecies] += (rhos[iSpecies]*v) * val_normal[1];
		val_Proj_Flux[nSpecies]   += (rho*v*u)          * val_normal[1];
		val_Proj_Flux[nSpecies+1] += (rho*v*v + P)      * val_normal[1];
		val_Proj_Flux[nSpecies+2] += (rho*v*H)          * val_normal[1];
    val_Proj_Flux[nSpecies+3] += (rhoEve*v)         * val_normal[1];
	}
	else {

    /*--- iDim = 0 (x-direction) ---*/
    for (iSpecies = 0; iSpecies < nSpecies; iSpecies++)
      val_Proj_Flux[iSpecies]  = (rhos[iSpecies]*u) * val_normal[0];
		val_Proj_Flux[nSpecies]    = (rho*u*u + P)      * val_normal[0];
		val_Proj_Flux[nSpecies+1]  = (rho*u*v)          * val_normal[0];
		val_Proj_Flux[nSpecies+2]  = (rho*u*w)          * val_normal[0];
		val_Proj_Flux[nSpecies+3]  = (rho*u*H)          * val_normal[0];
    val_Proj_Flux[nSpecies+4]  = (rhoEve*u)         * val_normal[0];

    /*--- iDim = 0 (y-direction) ---*/
    for (iSpecies = 0; iSpecies < nSpecies; iSpecies++)
      val_Proj_Flux[iSpecies] += (rhos[iSpecies]*v) * val_normal[1];
		val_Proj_Flux[nSpecies]   += (rho*v*u)          * val_normal[1];
		val_Proj_Flux[nSpecies+1] += (rho*v*v + P)      * val_normal[1];
		val_Proj_Flux[nSpecies+2] += (rho*v*w)          * val_normal[1];
		val_Proj_Flux[nSpecies+3] += (rho*v*H)          * val_normal[1];
    val_Proj_Flux[nSpecies+4] += (rhoEve*v)         * val_normal[1];

    /*--- iDim = 0 (z-direction) ---*/
    for (iSpecies = 0; iSpecies < nSpecies; iSpecies++)
      val_Proj_Flux[iSpecies] += (rhos[iSpecies]*w) * val_normal[2];
		val_Proj_Flux[nSpecies]   += (rho*w*u)          * val_normal[2];
		val_Proj_Flux[nSpecies+1] += (rho*w*v)          * val_normal[2];
		val_Proj_Flux[nSpecies+2] += (rho*w*w + P)      * val_normal[2];
		val_Proj_Flux[nSpecies+3] += (rho*w*H)          * val_normal[2];
    val_Proj_Flux[nSpecies+4] += (rhoEve*w)         * val_normal[2];
	}

  //	if (nDim == 2) {
  //		rhou = rho*val_velocity[0];
  //		rhov = rho*val_velocity[1];
  //
  //    /*--- iDim = 0 (x-direction) ---*/
  //    for (iSpecies = 0; iSpecies < nSpecies; iSpecies++)
  //      val_Proj_Flux[iSpecies] = rhou * (val_density[iSpecies]/rho) * val_normal[0];
  //		val_Proj_Flux[nSpecies]   = (rhou * val_velocity[0] + (*val_pressure)) * val_normal[0];
  //		val_Proj_Flux[nSpecies+1] = rhou * val_velocity[1] * val_normal[0];
  //		val_Proj_Flux[nSpecies+2] = rhou * (*val_enthalpy) * val_normal[0];
  //    val_Proj_Flux[nSpecies+3] = rhou * (*val_energy_ve) * val_normal[0];
  //
  //    /*---- iDim = 1 (y-direction) ---*/
  //    for (iSpecies = 0; iSpecies < nSpecies; iSpecies++)
  //      val_Proj_Flux[iSpecies] += rhov * (val_density[iSpecies]/rho) * val_normal[1];
  //		val_Proj_Flux[nSpecies]   += rhov * val_velocity[0] * val_normal[1];
  //		val_Proj_Flux[nSpecies+1] += (rhov * val_velocity[1] + (*val_pressure)) * val_normal[1];
  //		val_Proj_Flux[nSpecies+2] += rhov * (*val_enthalpy) * val_normal[1];
  //    val_Proj_Flux[nSpecies+3] += rhov * (*val_energy_ve) * val_normal[1];
  //	}
  //	else {
  //		rhou = (*val_density)*val_velocity[0];
  //		rhov = (*val_density)*val_velocity[1];
  //		rhow = (*val_density)*val_velocity[2];
  //
  //    /*--- iDim = 0 (x-direction) ---*/
  //    for (iSpecies = 0; iSpecies < nSpecies; iSpecies++)
  //      val_Proj_Flux[iSpecies] = rhou * (val_density[iSpecies]/rho) * val_normal[0];
  //		val_Proj_Flux[nSpecies]   = (rhou * val_velocity[0] + (*val_pressure)) * val_normal[0];
  //		val_Proj_Flux[nSpecies+1] = rhou * val_velocity[1] * val_normal[0];
  //		val_Proj_Flux[nSpecies+2] = rhou * val_velocity[2] * val_normal[0];
  //		val_Proj_Flux[nSpecies+3] = rhou * (*val_enthalpy) * val_normal[0];
  //    val_Proj_Flux[nSpecies+4] = rhou * (*val_energy_ve) * val_normal[0];
  //
  //    /*--- iDim = 0 (y-direction) ---*/
  //    for (iSpecies = 0; iSpecies < nSpecies; iSpecies++)
  //      val_Proj_Flux[iSpecies] += rhov * (val_density[iSpecies]/rho) * val_normal[1];
  //		val_Proj_Flux[nSpecies]   += rhov * val_velocity[0] * val_normal[1];
  //		val_Proj_Flux[nSpecies+1] += (rhov * val_velocity[1] + (*val_pressure)) * val_normal[1];
  //		val_Proj_Flux[nSpecies+2] += rhov * val_velocity[2] * val_normal[1];
  //		val_Proj_Flux[nSpecies+3] += rhov * (*val_enthalpy) * val_normal[1];
  //    val_Proj_Flux[nSpecies+4] += rhov * (*val_energy_ve) * val_normal[1];
  //
  //    /*--- iDim = 0 (z-direction) ---*/
  //    for (iSpecies = 0; iSpecies < nSpecies; iSpecies++)
  //      val_Proj_Flux[iSpecies] += rhow * (val_density[iSpecies]/rho) * val_normal[2];
  //		val_Proj_Flux[nSpecies]   += rhow * val_velocity[0] * val_normal[2];
  //		val_Proj_Flux[nSpecies+1] += rhow * val_velocity[1] * val_normal[2];
  //		val_Proj_Flux[nSpecies+2] += (rhow * val_velocity[2] + (*val_pressure)) * val_normal[2];
  //		val_Proj_Flux[nSpecies+3] += rhow * (*val_enthalpy) * val_normal[2];
  //    val_Proj_Flux[nSpecies+4] += rhow * (*val_energy_ve) * val_normal[2];
  //	}

  delete [] rhos;
}

void CNumerics::GetInviscidIncProjFlux(su2double *val_density,
                                           su2double *val_velocity,
                                           su2double *val_pressure,
                                           su2double *val_betainc2,
                                           su2double *val_enthalpy,
                                           su2double *val_normal,
                                           su2double *val_Proj_Flux) {
  su2double rhou, rhov, rhow;
    
  if (nDim == 2) {
    rhou = (*val_density)*val_velocity[0];
    rhov = (*val_density)*val_velocity[1];

    val_Proj_Flux[0] = rhou*val_normal[0] + rhov*val_normal[1];
    val_Proj_Flux[1] = (rhou*val_velocity[0]+(*val_pressure))*val_normal[0] + rhou*val_velocity[1]*val_normal[1];
    val_Proj_Flux[2] = rhov*val_velocity[0]*val_normal[0] + (rhov*val_velocity[1]+(*val_pressure))*val_normal[1];
    val_Proj_Flux[3] = (rhou*val_normal[0] + rhov*val_normal[1])*(*val_enthalpy);
  }
  else {
    rhou = (*val_density)*val_velocity[0];
    rhov = (*val_density)*val_velocity[1];
    rhow = (*val_density)*val_velocity[2];
    
    val_Proj_Flux[0] = rhou*val_normal[0] + rhov*val_normal[1] + rhow*val_normal[2];
    val_Proj_Flux[1] = (rhou*val_velocity[0]+(*val_pressure))*val_normal[0] + rhou*val_velocity[1]*val_normal[1] + rhou*val_velocity[2]*val_normal[2];
    val_Proj_Flux[2] = rhov*val_velocity[0]*val_normal[0] + (rhov*val_velocity[1]+(*val_pressure))*val_normal[1] + rhov*val_velocity[2]*val_normal[2];
    val_Proj_Flux[3] = rhow*val_velocity[0]*val_normal[0] + rhow*val_velocity[1]*val_normal[1] + (rhow*val_velocity[2]+(*val_pressure))*val_normal[2];
    val_Proj_Flux[4] = (rhou*val_normal[0] + rhov*val_normal[1] + rhow*val_normal[2])*(*val_enthalpy);
  }
  
}

void CNumerics::GetViscousProjFlux(su2double *val_primvar,
                                   su2double **val_gradprimvar,
                                   su2double *val_eve,
                                   su2double *val_normal,
                                   su2double *val_diffusioncoeff,
                                   su2double val_viscosity,
                                   su2double val_therm_conductivity,
                                   su2double val_therm_conductivity_ve,
                                   CConfig *config) {

  // Requires a slightly non-standard primitive vector:
  // Assumes -     V = [Y1, ... , Yn, T, Tve, ... ]
  // and gradient GV = [GY1, ... , GYn, GT, GTve, ... ]
  // rather than the standard V = [r1, ... , rn, T, Tve, ... ]

  bool ionization;
  unsigned short iSpecies, iVar, iDim, jDim, nHeavy, nEl;
  su2double *Ds, *V, **GV, mu, ktr, kve, div_vel;
  su2double Ru, RuSI;
  su2double rho, T, Tve;

  /*--- Initialize ---*/
  for (iVar = 0; iVar < nVar; iVar++) {
    Proj_Flux_Tensor[iVar] = 0.0;
    for (iDim = 0; iDim < nDim; iDim++)
      Flux_Tensor[iVar][iDim] = 0.0;
  }

  /*--- Read from CConfig ---*/
  ionization = config->GetIonization();
  if (ionization) { nHeavy = nSpecies-1; nEl = 1; }
  else            { nHeavy = nSpecies;   nEl = 0; }

  /*--- Rename for convenience ---*/
  Ds  = val_diffusioncoeff;
  mu  = val_viscosity;
  ktr = val_therm_conductivity;
  kve = val_therm_conductivity_ve;
  rho = val_primvar[RHO_INDEX];
  T   = val_primvar[T_INDEX];
  Tve = val_primvar[TVE_INDEX];
  RuSI= UNIVERSAL_GAS_CONSTANT;
  Ru  = 1000.0*RuSI;
  V   = val_primvar;
  GV  = val_gradprimvar;
  for (iSpecies = 0; iSpecies < nSpecies; iSpecies++)
    hs[iSpecies]  = var->CalcHs(config, T, val_eve[iSpecies], iSpecies);

  /*--- Calculate the velocity divergence ---*/
  div_vel = 0.0;
  for (iDim = 0 ; iDim < nDim; iDim++)
    div_vel += GV[VEL_INDEX+iDim][iDim];

  /*--- Pre-compute mixture quantities ---*/
  for (iDim = 0; iDim < nDim; iDim++) {
    Vector[iDim] = 0.0;
    for (iSpecies = 0; iSpecies < nHeavy; iSpecies++) {
      Vector[iDim] += rho*Ds[iSpecies]*GV[RHOS_INDEX+iSpecies][iDim];
    }
  }

  /*--- Compute the viscous stress tensor ---*/
  for (iDim = 0; iDim < nDim; iDim++)
    for (jDim = 0; jDim < nDim; jDim++)
      tau[iDim][jDim] = 0.0;
  for (iDim = 0 ; iDim < nDim; iDim++) {
    for (jDim = 0 ; jDim < nDim; jDim++) {
      tau[iDim][jDim] += mu * (val_gradprimvar[VEL_INDEX+jDim][iDim] +
          val_gradprimvar[VEL_INDEX+iDim][jDim]);
    }
    tau[iDim][iDim] -= TWO3*mu*div_vel;
  }

  /*--- Populate entries in the viscous flux vector ---*/
  for (iDim = 0; iDim < nDim; iDim++) {
    /*--- Species diffusion velocity ---*/
    for (iSpecies = 0; iSpecies < nHeavy; iSpecies++) {
      Flux_Tensor[iSpecies][iDim] = rho*Ds[iSpecies]*GV[RHOS_INDEX+iSpecies][iDim]
          - V[RHOS_INDEX+iSpecies]*Vector[iDim];
    }
    if (ionization) {
      cout << "GetViscProjFlux -- NEED TO IMPLEMENT IONIZED FUNCTIONALITY!!!" << endl;
      exit(1);
    }
    /*--- Shear stress related terms ---*/
    Flux_Tensor[nSpecies+nDim][iDim] = 0.0;
    for (jDim = 0; jDim < nDim; jDim++) {
      Flux_Tensor[nSpecies+jDim][iDim]  = tau[iDim][jDim];
      Flux_Tensor[nSpecies+nDim][iDim] += tau[iDim][jDim]*val_primvar[VEL_INDEX+jDim];
    }

    /*--- Diffusion terms ---*/
    for (iSpecies = 0; iSpecies < nHeavy; iSpecies++) {
      Flux_Tensor[nSpecies+nDim][iDim]   += Flux_Tensor[iSpecies][iDim] * hs[iSpecies];
      Flux_Tensor[nSpecies+nDim+1][iDim] += Flux_Tensor[iSpecies][iDim] * val_eve[iSpecies];
    }

    /*--- Heat transfer terms ---*/
    Flux_Tensor[nSpecies+nDim][iDim]   += ktr*GV[T_INDEX][iDim] +
        kve*GV[TVE_INDEX][iDim];
    Flux_Tensor[nSpecies+nDim+1][iDim] += kve*GV[TVE_INDEX][iDim];
  }

  for (iVar = 0; iVar < nVar; iVar++) {
    for (iDim = 0; iDim < nDim; iDim++) {
      Proj_Flux_Tensor[iVar] += Flux_Tensor[iVar][iDim]*val_normal[iDim];
    }
  }
}

void CNumerics::GetInviscidProjJac(su2double *val_velocity, su2double *val_energy,
                                   su2double *val_normal, su2double val_scale,
                                   su2double **val_Proj_Jac_Tensor) {
  AD_BEGIN_PASSIVE
  unsigned short iDim, jDim;
  su2double sqvel, proj_vel, phi, a1, a2;
  
  sqvel = 0.0; proj_vel = 0.0;
  for (iDim = 0; iDim < nDim; iDim++) {
    sqvel    += val_velocity[iDim]*val_velocity[iDim];
    proj_vel += val_velocity[iDim]*val_normal[iDim];
  }
  
  phi = 0.5*Gamma_Minus_One*sqvel;
  a1 = Gamma*(*val_energy)-phi;
  a2 = Gamma-1.0;
  
  val_Proj_Jac_Tensor[0][0] = 0.0;
  for (iDim = 0; iDim < nDim; iDim++)
    val_Proj_Jac_Tensor[0][iDim+1] = val_scale*val_normal[iDim];
  val_Proj_Jac_Tensor[0][nDim+1] = 0.0;
  
  for (iDim = 0; iDim < nDim; iDim++) {
    val_Proj_Jac_Tensor[iDim+1][0] = val_scale*(val_normal[iDim]*phi - val_velocity[iDim]*proj_vel);
    for (jDim = 0; jDim < nDim; jDim++)
      val_Proj_Jac_Tensor[iDim+1][jDim+1] = val_scale*(val_normal[jDim]*val_velocity[iDim]-a2*val_normal[iDim]*val_velocity[jDim]);
    val_Proj_Jac_Tensor[iDim+1][iDim+1] += val_scale*proj_vel;
    val_Proj_Jac_Tensor[iDim+1][nDim+1] = val_scale*a2*val_normal[iDim];
  }
  
  val_Proj_Jac_Tensor[nDim+1][0] = val_scale*proj_vel*(phi-a1);
  for (iDim = 0; iDim < nDim; iDim++)
    val_Proj_Jac_Tensor[nDim+1][iDim+1] = val_scale*(val_normal[iDim]*a1-a2*val_velocity[iDim]*proj_vel);
  val_Proj_Jac_Tensor[nDim+1][nDim+1] = val_scale*Gamma*proj_vel;
  AD_END_PASSIVE
}


void CNumerics::GetInviscidProjJac(su2double *val_velocity, su2double *val_enthalpy,
    su2double *val_chi, su2double *val_kappa,
    su2double *val_normal, su2double val_scale,
    su2double **val_Proj_Jac_Tensor) {
  AD_BEGIN_PASSIVE
  unsigned short iDim, jDim;
  su2double sqvel, proj_vel, phi, a1, a2;

  sqvel = 0.0; proj_vel = 0.0;
  for (iDim = 0; iDim < nDim; iDim++) {
    sqvel += val_velocity[iDim]*val_velocity[iDim];
    proj_vel += val_velocity[iDim]*val_normal[iDim];
  }

  phi = *val_chi + 0.5*sqvel*(*val_kappa);
  a1 = *val_enthalpy;
  a2 = *val_kappa;

  val_Proj_Jac_Tensor[0][0] = 0.0;
  for (iDim = 0; iDim < nDim; iDim++)
    val_Proj_Jac_Tensor[0][iDim+1] = val_scale*val_normal[iDim];
  val_Proj_Jac_Tensor[0][nDim+1] = 0.0;

  for (iDim = 0; iDim < nDim; iDim++) {
    val_Proj_Jac_Tensor[iDim+1][0] = val_scale*(val_normal[iDim]*phi - val_velocity[iDim]*proj_vel);
    for (jDim = 0; jDim < nDim; jDim++)
      val_Proj_Jac_Tensor[iDim+1][jDim+1] = val_scale*(val_normal[jDim]*val_velocity[iDim]-a2*val_normal[iDim]*val_velocity[jDim]);
    val_Proj_Jac_Tensor[iDim+1][iDim+1] += val_scale*proj_vel;
    val_Proj_Jac_Tensor[iDim+1][nDim+1] = val_scale*a2*val_normal[iDim];
  }

  val_Proj_Jac_Tensor[nDim+1][0] = val_scale*proj_vel*(phi-a1);
  for (iDim = 0; iDim < nDim; iDim++)
    val_Proj_Jac_Tensor[nDim+1][iDim+1] = val_scale*(val_normal[iDim]*a1-a2*val_velocity[iDim]*proj_vel);
  val_Proj_Jac_Tensor[nDim+1][nDim+1] = val_scale*(a2+1)*proj_vel;
  AD_END_PASSIVE
}

void CNumerics::GetInviscidProjJac(su2double *val_U,    su2double *val_V,
                                   su2double *val_dPdU, su2double *val_normal,
                                   su2double val_scale,
                                   su2double **val_Proj_Jac_Tensor) {

  unsigned short iDim, jDim, iVar, jVar, iSpecies, jSpecies;
  su2double proj_vel, rho, u[3], rhoEve, H;
  su2double *rhos;

  rhos = new su2double[nSpecies];

  /*--- Initialize the Jacobian tensor ---*/
  for (iVar = 0; iVar < nVar; iVar++)
    for (jVar = 0; jVar < nVar; jVar++)
      val_Proj_Jac_Tensor[iVar][jVar] = 0.0;

  /*--- Rename for convenience ---*/
  rho    = val_V[RHO_INDEX];
  H      = val_V[H_INDEX];
  //H = (val_U[nSpecies+nDim]+val_V[P_INDEX])/val_V[RHO_INDEX];
  rhoEve = val_U[nSpecies+nDim+1];
  for (iSpecies = 0; iSpecies < nSpecies; iSpecies++)
    rhos[iSpecies] = val_V[RHOS_INDEX+iSpecies];
  for (iDim = 0; iDim < nDim; iDim++)
    u[iDim] = val_V[VEL_INDEX+iDim];

  /*--- Calculate projected velocity ---*/
  proj_vel = 0.0;
  for (iDim = 0; iDim < nDim; iDim++) {
    proj_vel += u[iDim]*val_normal[iDim];
  }

  /*--- Species density rows ---*/
  for (iSpecies = 0; iSpecies < nSpecies; iSpecies++) {
    for (jSpecies = 0; jSpecies < nSpecies; jSpecies++) {
      val_Proj_Jac_Tensor[iSpecies][jSpecies] += -(rhos[iSpecies]/rho) * proj_vel;
    }
    val_Proj_Jac_Tensor[iSpecies][iSpecies]   += proj_vel;
    for (iDim  = 0; iDim < nDim; iDim++) {
      val_Proj_Jac_Tensor[iSpecies][nSpecies+iDim] += (rhos[iSpecies]/rho) * val_normal[iDim];
      val_Proj_Jac_Tensor[nSpecies+iDim][iSpecies] += val_dPdU[iSpecies]*val_normal[iDim] - proj_vel*u[iDim];
    }
    val_Proj_Jac_Tensor[nSpecies+nDim][iSpecies]   += (val_dPdU[iSpecies]-H) * proj_vel;
    val_Proj_Jac_Tensor[nSpecies+nDim+1][iSpecies] += -proj_vel * rhoEve/rho;
  }

  /*--- Momentum rows ---*/
  for (iDim = 0; iDim < nDim; iDim++) {
    for (jDim = 0; jDim < nDim; jDim++) {
      val_Proj_Jac_Tensor[nSpecies+iDim][nSpecies+jDim] += val_dPdU[nSpecies+jDim]*val_normal[iDim] + u[iDim]*val_normal[jDim];
    }
    val_Proj_Jac_Tensor[nSpecies+iDim][nSpecies+iDim]   += proj_vel;
    val_Proj_Jac_Tensor[nSpecies+iDim][nSpecies+nDim]   += val_dPdU[nSpecies+nDim]*val_normal[iDim];
    val_Proj_Jac_Tensor[nSpecies+iDim][nSpecies+nDim+1] += val_dPdU[nSpecies+nDim+1]*val_normal[iDim];
  }

  /*--- Total energy row ---*/
  for (iDim = 0; iDim < nDim; iDim++)
    val_Proj_Jac_Tensor[nSpecies+nDim][nSpecies+iDim] += val_dPdU[nSpecies+iDim]*proj_vel + H*val_normal[iDim];
  val_Proj_Jac_Tensor[nSpecies+nDim][nSpecies+nDim]   += (1+val_dPdU[nSpecies+nDim])*proj_vel;
  val_Proj_Jac_Tensor[nSpecies+nDim][nSpecies+nDim+1] +=  val_dPdU[nSpecies+nDim+1] *proj_vel;

  /*--- Vib.-el. energy row ---*/
  for (iDim = 0; iDim < nDim; iDim++)
    val_Proj_Jac_Tensor[nSpecies+nDim+1][nSpecies+iDim] = rhoEve/rho*val_normal[iDim];
  val_Proj_Jac_Tensor[nSpecies+nDim+1][nSpecies+nDim+1] = proj_vel;

  for (iVar = 0; iVar < nVar; iVar++)
    for (jVar = 0; jVar < nVar; jVar++)
      val_Proj_Jac_Tensor[iVar][jVar] = val_scale * val_Proj_Jac_Tensor[iVar][jVar];

  delete [] rhos;
}

void CNumerics::GetInviscidIncProjJac(su2double *val_density, su2double *val_velocity, su2double *val_betainc2, su2double *val_cp, su2double *val_temperature, su2double *val_dRhodT, su2double *val_normal,
    su2double val_scale, su2double **val_Proj_Jac_Tensor) {
  AD_BEGIN_PASSIVE
  unsigned short iDim;
  su2double proj_vel;

  proj_vel = 0.0;
  for (iDim = 0; iDim < nDim; iDim++)
    proj_vel += val_velocity[iDim]*val_normal[iDim];

  if (nDim == 2) {

    val_Proj_Jac_Tensor[0][0] = val_scale*(proj_vel/(*val_betainc2));
    val_Proj_Jac_Tensor[0][1] = val_scale*(val_normal[0]*(*val_density));
    val_Proj_Jac_Tensor[0][2] = val_scale*(val_normal[1]*(*val_density));
    val_Proj_Jac_Tensor[0][3] = val_scale*((*val_dRhodT)*proj_vel);

    val_Proj_Jac_Tensor[1][0] = val_scale*(val_normal[0] + val_velocity[0]*proj_vel/(*val_betainc2));
    val_Proj_Jac_Tensor[1][1] = val_scale*((*val_density)*(val_normal[0]*val_velocity[0] + proj_vel));
    val_Proj_Jac_Tensor[1][2] = val_scale*(val_normal[1]*(*val_density)*val_velocity[0]);
    val_Proj_Jac_Tensor[1][3] = val_scale*((*val_dRhodT)*val_velocity[0]*proj_vel);

    val_Proj_Jac_Tensor[2][0] = val_scale*(val_normal[1] + val_velocity[1]*proj_vel/(*val_betainc2));
    val_Proj_Jac_Tensor[2][1] = val_scale*(val_normal[0]*(*val_density)*val_velocity[1]);
    val_Proj_Jac_Tensor[2][2] = val_scale*((*val_density)*(proj_vel + val_normal[1]*val_velocity[1]));
    val_Proj_Jac_Tensor[2][3] = val_scale*((*val_dRhodT)*val_velocity[1]*proj_vel);

    val_Proj_Jac_Tensor[3][0] = val_scale*((*val_cp)*(*val_temperature)*proj_vel/(*val_betainc2));
    val_Proj_Jac_Tensor[3][1] = val_scale*((*val_cp)*(*val_temperature)*val_normal[0]*(*val_density));
    val_Proj_Jac_Tensor[3][2] = val_scale*((*val_cp)*(*val_temperature)*val_normal[1]*(*val_density));
    val_Proj_Jac_Tensor[3][3] = val_scale*((*val_cp)*((*val_temperature)*(*val_dRhodT) + (*val_density))*proj_vel);

  } else {

    val_Proj_Jac_Tensor[0][0] = val_scale*(proj_vel/(*val_betainc2));
    val_Proj_Jac_Tensor[0][1] = val_scale*(val_normal[0]*(*val_density));
    val_Proj_Jac_Tensor[0][2] = val_scale*(val_normal[1]*(*val_density));
    val_Proj_Jac_Tensor[0][3] = val_scale*(val_normal[2]*(*val_density));
    val_Proj_Jac_Tensor[0][4] = val_scale*((*val_dRhodT)*proj_vel);

    val_Proj_Jac_Tensor[1][0] = val_scale*(val_normal[0] + val_velocity[0]*proj_vel/(*val_betainc2));
    val_Proj_Jac_Tensor[1][1] = val_scale*((*val_density)*(val_normal[0]*val_velocity[0] + proj_vel));
    val_Proj_Jac_Tensor[1][2] = val_scale*(val_normal[1]*(*val_density)*val_velocity[0]);
    val_Proj_Jac_Tensor[1][3] = val_scale*(val_normal[2]*(*val_density)*val_velocity[0]);
    val_Proj_Jac_Tensor[1][4] = val_scale*((*val_dRhodT)*val_velocity[0]*proj_vel);

    val_Proj_Jac_Tensor[2][0] = val_scale*(val_normal[1] + val_velocity[1]*proj_vel/(*val_betainc2));
    val_Proj_Jac_Tensor[2][1] = val_scale*(val_normal[0]*(*val_density)*val_velocity[1]);
    val_Proj_Jac_Tensor[2][2] = val_scale*((*val_density)*(proj_vel + val_normal[1]*val_velocity[1]));
    val_Proj_Jac_Tensor[2][3] = val_scale*(val_normal[2]*(*val_density)*val_velocity[1]);
    val_Proj_Jac_Tensor[2][4] = val_scale*((*val_dRhodT)*val_velocity[1]*proj_vel);

    val_Proj_Jac_Tensor[3][0] = val_scale*(val_normal[2] + val_velocity[2]*proj_vel/(*val_betainc2));
    val_Proj_Jac_Tensor[3][1] = val_scale*(val_normal[0]*(*val_density)*val_velocity[2]);
    val_Proj_Jac_Tensor[3][2] = val_scale*(val_normal[1]*(*val_density)*val_velocity[2]);
    val_Proj_Jac_Tensor[3][3] = val_scale*((*val_density)*(proj_vel + val_normal[2]*val_velocity[2]));
    val_Proj_Jac_Tensor[3][4] = val_scale*((*val_dRhodT)*val_velocity[2]*proj_vel);

    val_Proj_Jac_Tensor[4][0] = val_scale*((*val_cp)*(*val_temperature)*proj_vel/(*val_betainc2));
    val_Proj_Jac_Tensor[4][1] = val_scale*((*val_cp)*(*val_temperature)*val_normal[0]*(*val_density));
    val_Proj_Jac_Tensor[4][2] = val_scale*((*val_cp)*(*val_temperature)*val_normal[1]*(*val_density));
    val_Proj_Jac_Tensor[4][3] = val_scale*((*val_cp)*(*val_temperature)*val_normal[2]*(*val_density));
    val_Proj_Jac_Tensor[4][4] = val_scale*((*val_cp)*((*val_temperature)*(*val_dRhodT) + (*val_density))*proj_vel);

  }
  AD_END_PASSIVE
}

void CNumerics::GetViscousProjJacs(su2double *val_Mean_PrimVar,
                                   su2double **val_Mean_GradPrimVar,
                                   su2double *val_Mean_Eve,
                                   su2double *val_Mean_Cvve,
                                   su2double *val_diffusion_coeff,
                                   su2double val_laminar_viscosity,
                                   su2double val_thermal_conductivity,
                                   su2double val_thermal_conductivity_ve,
                                   su2double val_dist_ij, su2double *val_normal,
                                   su2double val_dS, su2double *val_Fv,
                                   su2double **val_Jac_i, su2double **val_Jac_j,
                                   CConfig *config) {

  bool ionization;
  unsigned short iDim, iSpecies, jSpecies, iVar, jVar, kVar, nHeavy, nEl;
  su2double rho, rho_i, rho_j, vel[3], T, Tve, *xi, *Ms;
  su2double mu, ktr, kve, *Ds, dij, Ru, RuSI;
  su2double theta, thetax, thetay, thetaz;
  su2double etax, etay, etaz;
  su2double pix, piy, piz;
  su2double sumY, sumY_i, sumY_j;

  /*--- Initialize arrays ---*/
  for (iVar = 0; iVar < nVar; iVar++) {
    for (jVar = 0; jVar < nVar; jVar++) {
      dFdVi[iVar][jVar] = 0.0;
      dFdVj[iVar][jVar] = 0.0;
      dVdUi[iVar][jVar] = 0.0;
      dVdUj[iVar][jVar] = 0.0;
    }
  }

  /*--- Initialize the Jacobian matrices ---*/
  for (iVar = 0; iVar < nVar; iVar++) {
    for (jVar = 0; jVar < nVar; jVar++) {
      val_Jac_i[iVar][jVar] = 0.0;
      val_Jac_j[iVar][jVar] = 0.0;
    }
  }

  /*--- Initialize storage vectors & matrices ---*/
  for (iVar = 0; iVar < nSpecies; iVar++) {
    sumdFdYjh[iVar]   = 0.0;
    sumdFdYjeve[iVar] = 0.0;
    for (jVar = 0; jVar < nSpecies; jVar++) {
      dFdYi[iVar][jVar] = 0.0;
      dFdYj[iVar][jVar] = 0.0;
      dJdr_i[iVar][jVar] = 0.0;
      dJdr_j[iVar][jVar] = 0.0;
    }
  }

  /*--- Assign booleans from CConfig ---*/
  ionization = config->GetIonization();
  if (ionization) { nHeavy = nSpecies-1; nEl = 1; }
  else            { nHeavy = nSpecies;   nEl = 0; }

  /*--- Calculate preliminary geometrical quantities ---*/
  dij = val_dist_ij;
  theta = 0.0;
  for (iDim = 0; iDim < nDim; iDim++) {
    theta += val_normal[iDim]*val_normal[iDim];
  }


  /*--- Rename for convenience ---*/
  rho = val_Mean_PrimVar[RHO_INDEX];
  rho_i = V_i[RHO_INDEX];
  rho_j = V_j[RHO_INDEX];
  T   = val_Mean_PrimVar[T_INDEX];
  Tve = val_Mean_PrimVar[TVE_INDEX];
  Ds  = val_diffusion_coeff;
  mu  = val_laminar_viscosity;
  ktr = val_thermal_conductivity;
  kve = val_thermal_conductivity_ve;
  RuSI= UNIVERSAL_GAS_CONSTANT;
  Ru  = 1000.0*RuSI;
  Ms  = config->GetMolar_Mass();
  xi  = config->GetRotationModes();
  for (iSpecies = 0; iSpecies < nSpecies; iSpecies++) {
    Ys[iSpecies]   = val_Mean_PrimVar[RHOS_INDEX+iSpecies];
    Ys_i[iSpecies] = V_i[RHOS_INDEX+iSpecies]/V_i[RHO_INDEX];
    Ys_j[iSpecies] = V_j[RHOS_INDEX+iSpecies]/V_j[RHO_INDEX];
    hs[iSpecies]   = var->CalcHs(config, T, val_Mean_Eve[iSpecies], iSpecies);
    Cvtr[iSpecies] = (3.0/2.0 + xi[iSpecies]/2.0)*Ru/Ms[iSpecies];
  }
  for (iDim = 0; iDim < nDim; iDim++)
    vel[iDim] = val_Mean_PrimVar[VEL_INDEX+iDim];

  /*--- Calculate useful diffusion parameters ---*/
  // Summation term of the diffusion fluxes
  sumY = 0.0;
  sumY_i = 0.0;
  sumY_j = 0.0;
  for (iSpecies = 0; iSpecies < nHeavy; iSpecies++) {
    sumY_i += Ds[iSpecies]*theta/dij*Ys_i[iSpecies];
    sumY_j += Ds[iSpecies]*theta/dij*Ys_j[iSpecies];
    sumY   += Ds[iSpecies]*theta/dij*(Ys_j[iSpecies]-Ys_i[iSpecies]);
  }


  for (iSpecies = 0; iSpecies < nSpecies; iSpecies++) {
    for (jSpecies  = 0; jSpecies < nSpecies; jSpecies++) {

      // first term
      dJdr_j[iSpecies][jSpecies] +=  0.5*(Ds[iSpecies]*theta/dij *
                                          (Ys_j[iSpecies]*rho_i/rho_j +
                                           Ys_i[iSpecies]));
      dJdr_i[iSpecies][jSpecies] += -0.5*(Ds[iSpecies]*theta/dij *
                                          (Ys_j[iSpecies] +
                                           Ys_i[iSpecies]*rho_j/rho_i));

      // second term
      dJdr_j[iSpecies][jSpecies] +=
          0.25*(Ys_i[iSpecies] - rho_i/rho_j*Ys_j[iSpecies])*sumY
          + 0.25*(Ys_i[iSpecies]+Ys_j[iSpecies])*(rho_i+rho_j)*Ds[jSpecies]*theta/(dij*rho_j)
          - 0.25*(Ys_i[iSpecies]+Ys_j[iSpecies])*(rho_i+rho_j)*sumY_j/rho_j;

      dJdr_i[iSpecies][jSpecies] +=
          0.25*(-rho_j/rho_i*Ys_i[iSpecies]+Ys_j[iSpecies])*sumY
          - 0.25*(Ys_i[iSpecies]+Ys_j[iSpecies])*(rho_i+rho_j)*Ds[jSpecies]*theta/(dij*rho_i)
          + 0.25*(Ys_i[iSpecies]+Ys_j[iSpecies])*(rho_i+rho_j)*sumY_i/rho_i;
    }

    // first term
    dJdr_j[iSpecies][iSpecies] += -0.5*Ds[iSpecies]*theta/dij*(1+rho_i/rho_j);
    dJdr_i[iSpecies][iSpecies] +=  0.5*Ds[iSpecies]*theta/dij*(1+rho_j/rho_i);

    // second term
    dJdr_j[iSpecies][iSpecies] += 0.25*(1.0+rho_i/rho_j)*sumY;
    dJdr_i[iSpecies][iSpecies] += 0.25*(1.0+rho_j/rho_i)*sumY;
  }

  /*--- Calculate transformation matrix ---*/
  for (iSpecies = 0; iSpecies < nSpecies; iSpecies++) {
    dVdUi[iSpecies][iSpecies] = 1.0;
    dVdUj[iSpecies][iSpecies] = 1.0;
  }
  for (iDim = 0; iDim < nDim; iDim++) {
    for (iSpecies = 0; iSpecies < nSpecies; iSpecies++) {
      dVdUi[nSpecies+iDim][iSpecies] = -V_i[VEL_INDEX+iDim]/V_i[RHO_INDEX];
      dVdUj[nSpecies+iDim][iSpecies] = -V_j[VEL_INDEX+iDim]/V_j[RHO_INDEX];
    }
    dVdUi[nSpecies+iDim][nSpecies+iDim] = 1.0/V_i[RHO_INDEX];
    dVdUj[nSpecies+iDim][nSpecies+iDim] = 1.0/V_j[RHO_INDEX];
  }
  for (iVar = 0; iVar < nVar; iVar++) {
    dVdUi[nSpecies+nDim][iVar]   = dTdU_i[iVar];
    dVdUj[nSpecies+nDim][iVar]   = dTdU_j[iVar];
    dVdUi[nSpecies+nDim+1][iVar] = dTvedU_i[iVar];
    dVdUj[nSpecies+nDim+1][iVar] = dTvedU_j[iVar];
  }


  if (nDim == 2) {

    /*--- Geometry parameters ---*/
    thetax = theta + val_normal[0]*val_normal[0]/3.0;
    thetay = theta + val_normal[1]*val_normal[1]/3.0;
    etaz   = val_normal[0]*val_normal[1]/3.0;
    pix    = mu/dij * (thetax*vel[0] + etaz*vel[1]  );
    piy    = mu/dij * (etaz*vel[0]   + thetay*vel[1]);

    /*--- Populate primitive Jacobian ---*/

    // X-momentum
    dFdVj[nSpecies][nSpecies]     = mu*thetax/dij*val_dS;
    dFdVj[nSpecies][nSpecies+1]   = mu*etaz/dij*val_dS;

    // Y-momentum
    dFdVj[nSpecies+1][nSpecies]   = mu*etaz/dij*val_dS;
    dFdVj[nSpecies+1][nSpecies+1] = mu*thetay/dij*val_dS;

    // Energy
    dFdVj[nSpecies+2][nSpecies]   = pix*val_dS;
    dFdVj[nSpecies+2][nSpecies+1] = piy*val_dS;
    dFdVj[nSpecies+2][nSpecies+2] = ktr*theta/dij*val_dS;
    dFdVj[nSpecies+2][nSpecies+3] = kve*theta/dij*val_dS;

    // Vib-el Energy
    dFdVj[nSpecies+3][nSpecies+3] = kve*theta/dij*val_dS;

    for (iVar = 0; iVar < nVar; iVar++)
      for (jVar = 0; jVar < nVar; jVar++)
        dFdVi[iVar][jVar] = -dFdVj[iVar][jVar];

    // Common terms
    dFdVi[nSpecies+2][nSpecies]   += 0.5*val_Fv[nSpecies];
    dFdVj[nSpecies+2][nSpecies]   += 0.5*val_Fv[nSpecies];
    dFdVi[nSpecies+2][nSpecies+1] += 0.5*val_Fv[nSpecies+1];
    dFdVj[nSpecies+2][nSpecies+1] += 0.5*val_Fv[nSpecies+1];
    for (iSpecies = 0; iSpecies < nSpecies; iSpecies++) {
      dFdVi[nSpecies+2][nSpecies+2] += 0.5*val_Fv[iSpecies]*(Ru/Ms[iSpecies] +
                                                             Cvtr[iSpecies]   );
      dFdVj[nSpecies+2][nSpecies+2] += 0.5*val_Fv[iSpecies]*(Ru/Ms[iSpecies] +
                                                             Cvtr[iSpecies]   );
      dFdVi[nSpecies+2][nSpecies+3] += 0.5*val_Fv[iSpecies]*val_Mean_Cvve[iSpecies];
      dFdVj[nSpecies+2][nSpecies+3] += 0.5*val_Fv[iSpecies]*val_Mean_Cvve[iSpecies];
      dFdVi[nSpecies+3][nSpecies+3] += 0.5*val_Fv[iSpecies]*val_Mean_Cvve[iSpecies];
      dFdVj[nSpecies+3][nSpecies+3] += 0.5*val_Fv[iSpecies]*val_Mean_Cvve[iSpecies];
    }

    // Unique terms
    for (iSpecies = 0; iSpecies < nSpecies; iSpecies++) {
      for (jSpecies = 0; jSpecies < nSpecies; jSpecies++) {
        dFdVj[iSpecies][jSpecies]   += -dJdr_j[iSpecies][jSpecies]*val_dS;
        dFdVi[iSpecies][jSpecies]   += -dJdr_i[iSpecies][jSpecies]*val_dS;
        dFdVj[nSpecies+2][iSpecies] += -dJdr_j[jSpecies][iSpecies]*hs[jSpecies]*val_dS;
        dFdVi[nSpecies+2][iSpecies] += -dJdr_i[jSpecies][iSpecies]*hs[jSpecies]*val_dS;
        dFdVj[nSpecies+3][iSpecies] += -dJdr_j[jSpecies][iSpecies]*val_Mean_Eve[jSpecies]*val_dS;
        dFdVi[nSpecies+3][iSpecies] += -dJdr_i[jSpecies][iSpecies]*val_Mean_Eve[jSpecies]*val_dS;
      }
    }

  } //nDim == 2
  else {

    /*--- Geometry parameters ---*/
    thetax = theta + val_normal[0]*val_normal[0]/3.0;
    thetay = theta + val_normal[1]*val_normal[1]/3.0;
    thetaz = theta + val_normal[2]*val_normal[2]/3.0;
    etax   = val_normal[1]*val_normal[2]/3.0;
    etay   = val_normal[0]*val_normal[2]/3.0;
    etaz   = val_normal[0]*val_normal[1]/3.0;
    pix    = mu/dij * (thetax*vel[0] + etaz*vel[1]   + etay*vel[2]  );
    piy    = mu/dij * (etaz*vel[0]   + thetay*vel[1] + etax*vel[2]  );
    piz    = mu/dij * (etay*vel[0]   + etax*vel[1]   + thetaz*vel[2]);

    /*--- Populate primitive Jacobian ---*/

    // X-momentum
    dFdVj[nSpecies][nSpecies]     = mu*thetax/dij*val_dS;
    dFdVj[nSpecies][nSpecies+1]   = mu*etaz/dij*val_dS;
    dFdVj[nSpecies][nSpecies+2]   = mu*etay/dij*val_dS;

    // Y-momentum
    dFdVj[nSpecies+1][nSpecies]   = mu*etaz/dij*val_dS;
    dFdVj[nSpecies+1][nSpecies+1] = mu*thetay/dij*val_dS;
    dFdVj[nSpecies+1][nSpecies+2] = mu*etax/dij*val_dS;

    // Z-momentum
    dFdVj[nSpecies+2][nSpecies]   = mu*etay/dij*val_dS;
    dFdVj[nSpecies+2][nSpecies+1] = mu*etax/dij*val_dS;
    dFdVj[nSpecies+2][nSpecies+2] = mu*thetaz/dij*val_dS;

    // Energy
    dFdVj[nSpecies+3][nSpecies]   = pix*val_dS;
    dFdVj[nSpecies+3][nSpecies+1] = piy*val_dS;
    dFdVj[nSpecies+3][nSpecies+2] = piz*val_dS;
    dFdVj[nSpecies+3][nSpecies+3] = ktr*theta/dij*val_dS;
    dFdVj[nSpecies+3][nSpecies+4] = kve*theta/dij*val_dS;

    // Vib.-el energy
    dFdVj[nSpecies+4][nSpecies+4] = kve*theta/dij*val_dS;

    for (iVar = 0; iVar < nVar; iVar++)
      for (jVar = 0; jVar < nVar; jVar++)
        dFdVi[iVar][jVar] = -dFdVj[iVar][jVar];

    // Common terms
    for (iDim = 0; iDim < nDim; iDim++) {
      dFdVi[nSpecies+3][nSpecies+iDim]   += 0.5*val_Fv[nSpecies+iDim];
      dFdVj[nSpecies+3][nSpecies+iDim]   += 0.5*val_Fv[nSpecies+iDim];
    }
    for (iSpecies = 0; iSpecies < nSpecies; iSpecies++) {
      dFdVi[nSpecies+3][nSpecies+3] += 0.5*val_Fv[iSpecies]*(Ru/Ms[iSpecies] +
                                                             Cvtr[iSpecies]   );
      dFdVj[nSpecies+3][nSpecies+3] += 0.5*val_Fv[iSpecies]*(Ru/Ms[iSpecies] +
                                                             Cvtr[iSpecies]   );
      dFdVi[nSpecies+3][nSpecies+4] += 0.5*val_Fv[iSpecies]*val_Mean_Cvve[iSpecies];
      dFdVj[nSpecies+3][nSpecies+4] += 0.5*val_Fv[iSpecies]*val_Mean_Cvve[iSpecies];
      dFdVi[nSpecies+4][nSpecies+4] += 0.5*val_Fv[iSpecies]*val_Mean_Cvve[iSpecies];
      dFdVj[nSpecies+4][nSpecies+4] += 0.5*val_Fv[iSpecies]*val_Mean_Cvve[iSpecies];
    }

    // Unique terms
    for (iSpecies = 0; iSpecies < nSpecies; iSpecies++) {
      for (jSpecies = 0; jSpecies < nSpecies; jSpecies++) {
        dFdVj[iSpecies][jSpecies]   += -dJdr_j[iSpecies][jSpecies]*val_dS;
        dFdVi[iSpecies][jSpecies]   += -dJdr_i[iSpecies][jSpecies]*val_dS;
        dFdVj[nSpecies+3][iSpecies] += -dJdr_j[jSpecies][iSpecies]*hs[jSpecies]*val_dS;
        dFdVi[nSpecies+3][iSpecies] += -dJdr_i[jSpecies][iSpecies]*hs[jSpecies]*val_dS;
        dFdVj[nSpecies+4][iSpecies] += -dJdr_j[jSpecies][iSpecies]*val_Mean_Eve[jSpecies]*val_dS;
        dFdVi[nSpecies+4][iSpecies] += -dJdr_i[jSpecies][iSpecies]*val_Mean_Eve[jSpecies]*val_dS;
      }
    }

  } // nDim == 3

  /*--- dFv/dUij = dFv/dVij * dVij/dUij ---*/
  for (iVar = 0; iVar < nVar; iVar++)
    for (jVar = 0; jVar < nVar; jVar++)
      for (kVar = 0; kVar < nVar; kVar++) {
        val_Jac_i[iVar][jVar] += dFdVi[iVar][kVar]*dVdUi[kVar][jVar];
        val_Jac_j[iVar][jVar] += dFdVj[iVar][kVar]*dVdUj[kVar][jVar];
      }
}


void CNumerics::GetPreconditioner(su2double *val_density, su2double *val_velocity, su2double *val_betainc2, su2double *val_cp, su2double *val_temperature, su2double *val_drhodt, su2double **val_Precon) {
  unsigned short iDim, jDim;

  val_Precon[0][0] = 1.0/(*val_betainc2);
  for (iDim = 0; iDim < nDim; iDim++)
    val_Precon[iDim+1][0] = val_velocity[iDim]/(*val_betainc2);
  val_Precon[nDim+1][0] = (*val_cp)*(*val_temperature)/(*val_betainc2);

  for (jDim = 0; jDim < nDim; jDim++) {
    val_Precon[0][jDim+1] = 0.0;
    for (iDim = 0; iDim < nDim; iDim++) {
      if (iDim == jDim) val_Precon[iDim+1][jDim+1] = (*val_density);
      else val_Precon[iDim+1][jDim+1] = 0.0;
    }
    val_Precon[nDim+1][jDim+1] = 0.0;
  }

  val_Precon[0][nDim+1] = (*val_drhodt);
  for (iDim = 0; iDim < nDim; iDim++)
    val_Precon[iDim+1][nDim+1] = val_velocity[iDim]*(*val_drhodt);
  val_Precon[nDim+1][nDim+1] = (*val_cp)*((*val_drhodt)*(*val_temperature) + (*val_density));

}

void CNumerics::GetPreconditionedProjJac(su2double *val_density, su2double *val_lambda, su2double *val_betainc2, su2double *val_normal, su2double **val_invPrecon_A) {
  unsigned short iDim, jDim, kDim;

  val_invPrecon_A[0][0] = val_lambda[nDim]/2.0 + val_lambda[nDim+1]/2.0;
  for (iDim = 0; iDim < nDim; iDim++)
    val_invPrecon_A[iDim+1][0] = val_normal[iDim]*(-val_lambda[nDim] + val_lambda[nDim+1])/(2.0*sqrt((*val_betainc2))*(*val_density));
  val_invPrecon_A[nDim+1][0] = 0.0;

  for (jDim = 0; jDim < nDim; jDim++) {
    val_invPrecon_A[0][jDim+1] = sqrt((*val_betainc2))*val_normal[jDim]*(*val_density)*(-val_lambda[nDim] + val_lambda[nDim+1])/(2.0);
    for (iDim = 0; iDim < nDim; iDim++) {
      if (iDim == jDim) {
        val_invPrecon_A[iDim+1][jDim+1] = (val_lambda[nDim] + val_lambda[nDim+1])*val_normal[iDim]*val_normal[iDim]/2.0;
        for (kDim = 0; kDim < nDim; kDim++) {
          if (kDim != iDim) val_invPrecon_A[iDim+1][jDim+1] += 2.0*val_lambda[0]*val_normal[kDim]*val_normal[kDim];
        }
      }
      else {
        val_invPrecon_A[iDim+1][jDim+1] = val_normal[iDim]*val_normal[jDim]*(-2.0*val_lambda[0] + val_lambda[nDim] + val_lambda[nDim+1])/(2.0);
      }
    }
    val_invPrecon_A[nDim+1][jDim+1] = 0.0;
  }

  val_invPrecon_A[0][nDim+1] = 0.0;
  for (iDim = 0; iDim < nDim; iDim++)
    val_invPrecon_A[iDim+1][nDim+1] = 0.0;
  val_invPrecon_A[nDim+1][nDim+1] = val_lambda[nDim-1];
  
}

void CNumerics::SetPastSol (su2double *val_u_nM1, su2double *val_u_n, su2double *val_u_nP1) {
  unsigned short iVar;

  for (iVar = 0; iVar < nVar; iVar++) {
    U_nM1[iVar] = val_u_nM1[iVar];
    U_n[iVar] = val_u_n[iVar];
    U_nP1[iVar] = val_u_nP1[iVar];
  }

}

void CNumerics::SetPastVolume (su2double val_volume_nM1, su2double val_volume_n, su2double val_volume_nP1) {
  Volume_nM1 = val_volume_nM1;
  Volume_n = val_volume_n;
  Volume_nP1 = val_volume_nP1;
}

void CNumerics::GetPMatrix(su2double *val_density, su2double *val_velocity,
                           su2double *val_soundspeed, su2double *val_normal, su2double **val_p_tensor) {
  
  su2double sqvel, rhooc, rhoxc;
  //su2double c2;
  
  rhooc = *val_density / *val_soundspeed;
  rhoxc = *val_density * *val_soundspeed;
  //c2 = *val_soundspeed * *val_soundspeed;
  
  if (nDim == 2) {
    
    sqvel = val_velocity[0]*val_velocity[0]+val_velocity[1]*val_velocity[1];
    
    val_p_tensor[0][0] = 1.0;
    val_p_tensor[0][1]=0.0;
    val_p_tensor[0][2]=0.5*rhooc;
    val_p_tensor[0][3]=0.5*rhooc;
    
    val_p_tensor[1][0]=val_velocity[0];
    val_p_tensor[1][1]=*val_density*val_normal[1];
    val_p_tensor[1][2]=0.5*(val_velocity[0]*rhooc+val_normal[0]**val_density);
    val_p_tensor[1][3]=0.5*(val_velocity[0]*rhooc-val_normal[0]**val_density);
    
    val_p_tensor[2][0]=val_velocity[1];
    val_p_tensor[2][1]=-*val_density*val_normal[0];
    val_p_tensor[2][2]=0.5*(val_velocity[1]*rhooc+val_normal[1]**val_density);
    val_p_tensor[2][3]=0.5*(val_velocity[1]*rhooc-val_normal[1]**val_density);
    
    val_p_tensor[3][0]=0.5*sqvel;
    val_p_tensor[3][1]=*val_density*val_velocity[0]*val_normal[1]-*val_density*val_velocity[1]*val_normal[0];
    val_p_tensor[3][2]=0.5*(0.5*sqvel*rhooc+*val_density*val_velocity[0]*val_normal[0]+*val_density*val_velocity[1]*val_normal[1]+rhoxc/Gamma_Minus_One);
    val_p_tensor[3][3]=0.5*(0.5*sqvel*rhooc-*val_density*val_velocity[0]*val_normal[0]-*val_density*val_velocity[1]*val_normal[1]+rhoxc/Gamma_Minus_One);
    
  }
  else {
    
    sqvel = val_velocity[0]*val_velocity[0]+val_velocity[1]*val_velocity[1]+val_velocity[2]*val_velocity[2];
    
    val_p_tensor[0][0]=val_normal[0];
    val_p_tensor[0][1]=val_normal[1];
    val_p_tensor[0][2]=val_normal[2];
    val_p_tensor[0][3]=0.5*rhooc;
    val_p_tensor[0][4]=0.5*rhooc;
    
    val_p_tensor[1][0]=val_velocity[0]*val_normal[0];
    val_p_tensor[1][1]=val_velocity[0]*val_normal[1]-*val_density*val_normal[2];
    val_p_tensor[1][2]=val_velocity[0]*val_normal[2]+*val_density*val_normal[1];
    val_p_tensor[1][3]=0.5*(val_velocity[0]*rhooc+*val_density*val_normal[0]);
    val_p_tensor[1][4]=0.5*(val_velocity[0]*rhooc-*val_density*val_normal[0]);
    
    val_p_tensor[2][0]=val_velocity[1]*val_normal[0]+*val_density*val_normal[2];
    val_p_tensor[2][1]=val_velocity[1]*val_normal[1];
    val_p_tensor[2][2]=val_velocity[1]*val_normal[2]-*val_density*val_normal[0];
    val_p_tensor[2][3]=0.5*(val_velocity[1]*rhooc+*val_density*val_normal[1]);
    val_p_tensor[2][4]=0.5*(val_velocity[1]*rhooc-*val_density*val_normal[1]);
    
    val_p_tensor[3][0]=val_velocity[2]*val_normal[0]-*val_density*val_normal[1];
    val_p_tensor[3][1]=val_velocity[2]*val_normal[1]+*val_density*val_normal[0];
    val_p_tensor[3][2]=val_velocity[2]*val_normal[2];
    val_p_tensor[3][3]=0.5*(val_velocity[2]*rhooc+*val_density*val_normal[2]);
    val_p_tensor[3][4]=0.5*(val_velocity[2]*rhooc-*val_density*val_normal[2]);
    
    val_p_tensor[4][0]=0.5*sqvel*val_normal[0]+*val_density*val_velocity[1]*val_normal[2]-*val_density*val_velocity[2]*val_normal[1];
    val_p_tensor[4][1]=0.5*sqvel*val_normal[1]-*val_density*val_velocity[0]*val_normal[2]+*val_density*val_velocity[2]*val_normal[0];
    val_p_tensor[4][2]=0.5*sqvel*val_normal[2]+*val_density*val_velocity[0]*val_normal[1]-*val_density*val_velocity[1]*val_normal[0];
    val_p_tensor[4][3]=0.5*(0.5*sqvel*rhooc+*val_density*(val_velocity[0]*val_normal[0]+val_velocity[1]*val_normal[1]+val_velocity[2]*val_normal[2])+rhoxc/Gamma_Minus_One);
    val_p_tensor[4][4]=0.5*(0.5*sqvel*rhooc-*val_density*(val_velocity[0]*val_normal[0]+val_velocity[1]*val_normal[1]+val_velocity[2]*val_normal[2])+rhoxc/Gamma_Minus_One);
    
  }
  
}

void CNumerics::GetPMatrix(su2double *val_density, su2double *val_velocity,
    su2double *val_soundspeed, su2double *val_enthalpy, su2double *val_chi, su2double *val_kappa, su2double *val_normal, su2double **val_p_tensor) {

  su2double sqvel, rhooc, zeta;
  //su2double rhoxc, c2;
  
  rhooc = *val_density / *val_soundspeed;
  //rhoxc = *val_density * *val_soundspeed;
  //c2 = *val_soundspeed * *val_soundspeed;

  if (nDim == 2) {
    sqvel = val_velocity[0]*val_velocity[0]+val_velocity[1]*val_velocity[1];
    zeta = sqvel - (*val_kappa*0.5*sqvel + *val_chi)/(*val_kappa);

    val_p_tensor[0][0] = 1.0;
    val_p_tensor[0][1]=0.0;
    val_p_tensor[0][2]=0.5*rhooc;
    val_p_tensor[0][3]=0.5*rhooc;

    val_p_tensor[1][0]=val_velocity[0];
    val_p_tensor[1][1]=*val_density*val_normal[1];
    val_p_tensor[1][2]=0.5*(val_velocity[0]*rhooc+val_normal[0]**val_density);
    val_p_tensor[1][3]=0.5*(val_velocity[0]*rhooc-val_normal[0]**val_density);

    val_p_tensor[2][0]=val_velocity[1];
    val_p_tensor[2][1]=-*val_density*val_normal[0];
    val_p_tensor[2][2]=0.5*(val_velocity[1]*rhooc+val_normal[1]**val_density);
    val_p_tensor[2][3]=0.5*(val_velocity[1]*rhooc-val_normal[1]**val_density);

    val_p_tensor[3][0]= zeta;
    val_p_tensor[3][1]=*val_density*val_velocity[0]*val_normal[1]-*val_density*val_velocity[1]*val_normal[0];
    val_p_tensor[3][2]=0.5*(*val_enthalpy*rhooc+*val_density*val_velocity[0]*val_normal[0]+*val_density*val_velocity[1]*val_normal[1]);
    val_p_tensor[3][3]=0.5*(*val_enthalpy*rhooc-*val_density*val_velocity[0]*val_normal[0]-*val_density*val_velocity[1]*val_normal[1]);
  }
  else {
    sqvel = val_velocity[0]*val_velocity[0]+val_velocity[1]*val_velocity[1]+val_velocity[2]*val_velocity[2];
    zeta = sqvel - (*val_kappa*0.5*sqvel + *val_chi)/(*val_kappa);

    val_p_tensor[0][0]=val_normal[0];
    val_p_tensor[0][1]=val_normal[1];
    val_p_tensor[0][2]=val_normal[2];
    val_p_tensor[0][3]=0.5*rhooc;
    val_p_tensor[0][4]=0.5*rhooc;

    val_p_tensor[1][0]=val_velocity[0]*val_normal[0];
    val_p_tensor[1][1]=val_velocity[0]*val_normal[1]-*val_density*val_normal[2];
    val_p_tensor[1][2]=val_velocity[0]*val_normal[2]+*val_density*val_normal[1];
    val_p_tensor[1][3]=0.5*(val_velocity[0]*rhooc+*val_density*val_normal[0]);
    val_p_tensor[1][4]=0.5*(val_velocity[0]*rhooc-*val_density*val_normal[0]);

    val_p_tensor[2][0]=val_velocity[1]*val_normal[0]+*val_density*val_normal[2];
    val_p_tensor[2][1]=val_velocity[1]*val_normal[1];
    val_p_tensor[2][2]=val_velocity[1]*val_normal[2]-*val_density*val_normal[0];
    val_p_tensor[2][3]=0.5*(val_velocity[1]*rhooc+*val_density*val_normal[1]);
    val_p_tensor[2][4]=0.5*(val_velocity[1]*rhooc-*val_density*val_normal[1]);

    val_p_tensor[3][0]=val_velocity[2]*val_normal[0]-*val_density*val_normal[1];
    val_p_tensor[3][1]=val_velocity[2]*val_normal[1]+*val_density*val_normal[0];
    val_p_tensor[3][2]=val_velocity[2]*val_normal[2];
    val_p_tensor[3][3]=0.5*(val_velocity[2]*rhooc+*val_density*val_normal[2]);
    val_p_tensor[3][4]=0.5*(val_velocity[2]*rhooc-*val_density*val_normal[2]);

    val_p_tensor[4][0]=zeta*val_normal[0]+*val_density*val_velocity[1]*val_normal[2]-*val_density*val_velocity[2]*val_normal[1];
    val_p_tensor[4][1]=zeta*val_normal[1]-*val_density*val_velocity[0]*val_normal[2]+*val_density*val_velocity[2]*val_normal[0];
    val_p_tensor[4][2]=zeta*val_normal[2]+*val_density*val_velocity[0]*val_normal[1]-*val_density*val_velocity[1]*val_normal[0];
    val_p_tensor[4][3]=0.5*(*val_enthalpy*rhooc+*val_density*(val_velocity[0]*val_normal[0]+val_velocity[1]*val_normal[1]+val_velocity[2]*val_normal[2]));
    val_p_tensor[4][4]=0.5*(*val_enthalpy*rhooc-*val_density*(val_velocity[0]*val_normal[0]+val_velocity[1]*val_normal[1]+val_velocity[2]*val_normal[2]));
  }

}

void CNumerics::GetPMatrix(su2double *U, su2double *V, su2double *val_dPdU,
                           su2double *val_normal, su2double *l, su2double *m,
                           su2double **val_p_tensor) {

  // P matrix is equivalent to the L matrix in Gnoffo
  unsigned short iSpecies, iDim, iVar, jVar;
 	su2double sqvel, rho, a, a2, eve;
  su2double vU, vV, vW;

  /*--- Initialize the P matrix to zero ---*/
  for (iVar = 0; iVar < nVar; iVar++)
    for (jVar = 0; jVar < nVar; jVar++)
      val_p_tensor[iVar][jVar] = 0.0;

  /*--- Pre-compute useful quantities ---*/
  sqvel = 0.0;
  rho = V[RHO_INDEX];
  eve = U[nSpecies+nDim+1]/rho;
  vU = 0.0;  vV = 0.0;  vW = 0.0;
  for (iDim = 0; iDim < nDim; iDim++) {
    vU    += V[VEL_INDEX+iDim] * val_normal[iDim];
    vV    += V[VEL_INDEX+iDim] * l[iDim];
    vW    += V[VEL_INDEX+iDim] * m[iDim];
    sqvel += V[VEL_INDEX+iDim] * V[VEL_INDEX+iDim];
  }
  a  = V[A_INDEX];
  a2 = V[A_INDEX]*V[A_INDEX];

	if(nDim == 2) {
		cout << "P matrix not implemented for 2-D Flows!!" << endl;
	}
	else {

    for (iSpecies = 0; iSpecies < nSpecies; iSpecies++) {
      val_p_tensor[iSpecies][iSpecies]   = 1.0/a2;
      val_p_tensor[iSpecies][nSpecies]   = 0.0;
      val_p_tensor[iSpecies][nSpecies+1] = 0.0;
      val_p_tensor[iSpecies][nSpecies+2] = V[RHOS_INDEX+iSpecies] / (2.0*rho*a2);
      val_p_tensor[iSpecies][nSpecies+3] = V[RHOS_INDEX+iSpecies] / (2.0*rho*a2);
      val_p_tensor[iSpecies][nSpecies+4] = 0.0;

      val_p_tensor[nSpecies][iSpecies]   = V[VEL_INDEX]   / a2;
      val_p_tensor[nSpecies+1][iSpecies] = V[VEL_INDEX+1] / a2;
      val_p_tensor[nSpecies+2][iSpecies] = V[VEL_INDEX+2] / a2;
      val_p_tensor[nSpecies+3][iSpecies] = (val_dPdU[nSpecies+3]*sqvel-val_dPdU[iSpecies])
                                         / (val_dPdU[nSpecies+3]*a2);
      val_p_tensor[nSpecies+4][iSpecies] = 0.0;
    }

		val_p_tensor[nSpecies][nSpecies]     = l[0];
    val_p_tensor[nSpecies][nSpecies+1]   = m[0];
    val_p_tensor[nSpecies][nSpecies+2]   = (V[VEL_INDEX]+a*val_normal[0]) / (2.0*a2);
    val_p_tensor[nSpecies][nSpecies+3]   = (V[VEL_INDEX]-a*val_normal[0]) / (2.0*a2);
    val_p_tensor[nSpecies][nSpecies+4]   = 0.0;

    val_p_tensor[nSpecies+1][nSpecies]   = l[1];
    val_p_tensor[nSpecies+1][nSpecies+1] = m[1];
    val_p_tensor[nSpecies+1][nSpecies+2] = (V[VEL_INDEX+1]+a*val_normal[1]) / (2.0*a2);
    val_p_tensor[nSpecies+1][nSpecies+3] = (V[VEL_INDEX+1]-a*val_normal[1]) / (2.0*a2);
    val_p_tensor[nSpecies+1][nSpecies+4] = 0.0;

    val_p_tensor[nSpecies+2][nSpecies]   = l[2];
    val_p_tensor[nSpecies+2][nSpecies+1] = m[2];
    val_p_tensor[nSpecies+2][nSpecies+2] = (V[VEL_INDEX+2]+a*val_normal[2]) / (2.0*a2);
    val_p_tensor[nSpecies+2][nSpecies+3] = (V[VEL_INDEX+2]-a*val_normal[2]) / (2.0*a2);
    val_p_tensor[nSpecies+2][nSpecies+4] = 0.0;

    val_p_tensor[nSpecies+3][nSpecies]   = vV;
    val_p_tensor[nSpecies+3][nSpecies+1] = vW;
    val_p_tensor[nSpecies+3][nSpecies+2] = ((V[H_INDEX])+a*vU) / (2.0*a2);
    val_p_tensor[nSpecies+3][nSpecies+3] = ((V[H_INDEX])-a*vU) / (2.0*a2);
    val_p_tensor[nSpecies+3][nSpecies+4] = -val_dPdU[nSpecies+nDim+1] / (val_dPdU[nSpecies+nDim]*a2);

    val_p_tensor[nSpecies+4][nSpecies]   = 0.0;
    val_p_tensor[nSpecies+4][nSpecies+1] = 0.0;
    val_p_tensor[nSpecies+4][nSpecies+2] = eve / (2.0*a2);
    val_p_tensor[nSpecies+4][nSpecies+3] = eve / (2.0*a2);
    val_p_tensor[nSpecies+4][nSpecies+4] = 1.0 / a2;
	}
}

void CNumerics::GetPMatrix_inv(su2double *val_density, su2double *val_velocity,
    su2double *val_soundspeed, su2double *val_normal, su2double **val_invp_tensor) {
  
  su2double rhoxc, c2, gm1, k0orho, k1orho, gm1_o_c2, gm1_o_rhoxc, sqvel;

  rhoxc = *val_density * *val_soundspeed;
  c2 = *val_soundspeed * *val_soundspeed;
  gm1 = Gamma_Minus_One;
  k0orho = val_normal[0] / *val_density;
  k1orho = val_normal[1] / *val_density;
  gm1_o_c2 = gm1/c2;
  gm1_o_rhoxc = gm1/rhoxc;

  if (nDim == 3) {
    
    sqvel = val_velocity[0]*val_velocity[0]+val_velocity[1]*val_velocity[1]+val_velocity[2]*val_velocity[2];

    val_invp_tensor[0][0]=val_normal[0]-val_normal[2]*val_velocity[1] / *val_density+val_normal[1]*val_velocity[2] / *val_density-val_normal[0]*0.5*gm1*sqvel/c2;
    val_invp_tensor[0][1]=val_normal[0]*gm1*val_velocity[0]/c2;
    val_invp_tensor[0][2]=val_normal[2] / *val_density+val_normal[0]*gm1*val_velocity[1]/c2;
    val_invp_tensor[0][3]=-val_normal[1] / *val_density+val_normal[0]*gm1*val_velocity[2]/c2;
    val_invp_tensor[0][4]=-val_normal[0]*gm1/c2;

    val_invp_tensor[1][0]=val_normal[1]+val_normal[2]*val_velocity[0] / *val_density-val_normal[0]*val_velocity[2] / *val_density-val_normal[1]*0.5*gm1*sqvel/c2;
    val_invp_tensor[1][1]=-val_normal[2] / *val_density+val_normal[1]*gm1*val_velocity[0]/c2;
    val_invp_tensor[1][2]=val_normal[1]*gm1*val_velocity[1]/c2;
    val_invp_tensor[1][3]=val_normal[0] / *val_density+val_normal[1]*gm1*val_velocity[2]/c2;
    val_invp_tensor[1][4]=-val_normal[1]*gm1/c2;

    val_invp_tensor[2][0]=val_normal[2]-val_normal[1]*val_velocity[0] / *val_density+val_normal[0]*val_velocity[1] / *val_density-val_normal[2]*0.5*gm1*sqvel/c2;
    val_invp_tensor[2][1]=val_normal[1] / *val_density+val_normal[2]*gm1*val_velocity[0]/c2;
    val_invp_tensor[2][2]=-val_normal[0] / *val_density+val_normal[2]*gm1*val_velocity[1]/c2;
    val_invp_tensor[2][3]=val_normal[2]*gm1*val_velocity[2]/c2;
    val_invp_tensor[2][4]=-val_normal[2]*gm1/c2;

    val_invp_tensor[3][0]=-(val_normal[0]*val_velocity[0]+val_normal[1]*val_velocity[1]+val_normal[2]*val_velocity[2]) / *val_density+0.5*gm1*sqvel/rhoxc;
    val_invp_tensor[3][1]=val_normal[0] / *val_density-gm1*val_velocity[0]/rhoxc;
    val_invp_tensor[3][2]=val_normal[1] / *val_density-gm1*val_velocity[1]/rhoxc;
    val_invp_tensor[3][3]=val_normal[2] / *val_density-gm1*val_velocity[2]/rhoxc;
    val_invp_tensor[3][4]=Gamma_Minus_One/rhoxc;

    val_invp_tensor[4][0]=(val_normal[0]*val_velocity[0]+val_normal[1]*val_velocity[1]+val_normal[2]*val_velocity[2]) / *val_density+0.5*gm1*sqvel/rhoxc;
    val_invp_tensor[4][1]=-val_normal[0] / *val_density-gm1*val_velocity[0]/rhoxc;
    val_invp_tensor[4][2]=-val_normal[1] / *val_density-gm1*val_velocity[1]/rhoxc;
    val_invp_tensor[4][3]=-val_normal[2] / *val_density-gm1*val_velocity[2]/rhoxc;
    val_invp_tensor[4][4]=Gamma_Minus_One/rhoxc;
    
  }
  if (nDim == 2) {
    
    sqvel = val_velocity[0]*val_velocity[0]+val_velocity[1]*val_velocity[1];

    val_invp_tensor[0][0] = 1.0-0.5*gm1_o_c2*sqvel;
    val_invp_tensor[0][1]=gm1_o_c2*val_velocity[0];
    val_invp_tensor[0][2]=gm1_o_c2*val_velocity[1];
    val_invp_tensor[0][3]=-gm1_o_c2;

    val_invp_tensor[1][0]=-k1orho*val_velocity[0]+k0orho*val_velocity[1];
    val_invp_tensor[1][1]=k1orho;
    val_invp_tensor[1][2]=-k0orho;
    val_invp_tensor[1][3]=0.0;

    val_invp_tensor[2][0]=-k0orho*val_velocity[0]-k1orho*val_velocity[1]+0.5*gm1_o_rhoxc*sqvel;
    val_invp_tensor[2][1]=k0orho-gm1_o_rhoxc*val_velocity[0];
    val_invp_tensor[2][2]=k1orho-gm1_o_rhoxc*val_velocity[1];
    val_invp_tensor[2][3]=gm1_o_rhoxc;

    val_invp_tensor[3][0]=k0orho*val_velocity[0]+k1orho*val_velocity[1]+0.5*gm1_o_rhoxc*sqvel;
    val_invp_tensor[3][1]=-k0orho-gm1_o_rhoxc*val_velocity[0];
    val_invp_tensor[3][2]=-k1orho-gm1_o_rhoxc*val_velocity[1];
    val_invp_tensor[3][3]=gm1_o_rhoxc;
    
  }
}

void CNumerics::GetPMatrix_inv(su2double **val_invp_tensor, su2double *val_density, su2double *val_velocity,
    su2double *val_soundspeed, su2double *val_chi, su2double *val_kappa, su2double *val_normal) {

  su2double rhoxc, c2, k0orho, k1orho, sqvel, k_o_c2, k_o_rhoxc, dp_drho;

  rhoxc = *val_density * *val_soundspeed;
  c2 = *val_soundspeed * *val_soundspeed;
  k0orho = val_normal[0] / *val_density;
  k1orho = val_normal[1] / *val_density;
  k_o_c2 = (*val_kappa)/c2;
  k_o_rhoxc = (*val_kappa)/rhoxc;


  if (nDim == 3) {
    sqvel = val_velocity[0]*val_velocity[0]+val_velocity[1]*val_velocity[1]+val_velocity[2]*val_velocity[2];
    dp_drho = *val_chi + 0.5*sqvel*(*val_kappa);

    val_invp_tensor[0][0]=val_normal[0]-val_normal[2]*val_velocity[1] / *val_density + val_normal[1]*val_velocity[2] / *val_density - val_normal[0]*dp_drho/c2;
    val_invp_tensor[0][1]=val_normal[0]*val_velocity[0]*k_o_c2;
    val_invp_tensor[0][2]=val_normal[2] / *val_density + val_normal[0]*val_velocity[1]*k_o_c2;
    val_invp_tensor[0][3]=-val_normal[1] / *val_density + val_normal[0]*val_velocity[2]*k_o_c2;
    val_invp_tensor[0][4]=-val_normal[0]*k_o_c2;

    val_invp_tensor[1][0]=val_normal[1]+val_normal[2]*val_velocity[0] / *val_density - val_normal[0]*val_velocity[2] / *val_density - val_normal[1]*dp_drho/c2;
    val_invp_tensor[1][1]=-val_normal[2] / *val_density + val_normal[1]*val_velocity[0]*k_o_c2;
    val_invp_tensor[1][2]=val_normal[1]*val_velocity[1]*k_o_c2;
    val_invp_tensor[1][3]=val_normal[0] / *val_density + val_normal[1]*val_velocity[2]*k_o_c2;
    val_invp_tensor[1][4]=-val_normal[1]*k_o_c2;

    val_invp_tensor[2][0]=val_normal[2]-val_normal[1]*val_velocity[0] / *val_density + val_normal[0]*val_velocity[1] / *val_density - val_normal[2]*dp_drho/c2;
    val_invp_tensor[2][1]=val_normal[1] / *val_density + val_normal[2]*val_velocity[0]*k_o_c2;
    val_invp_tensor[2][2]=-val_normal[0] / *val_density + val_normal[2]*val_velocity[1]*k_o_c2;
    val_invp_tensor[2][3]=val_normal[2]*val_velocity[2]*k_o_c2;
    val_invp_tensor[2][4]=-val_normal[2]*k_o_c2;

    val_invp_tensor[3][0]=-(val_normal[0]*val_velocity[0]+val_normal[1]*val_velocity[1]+val_normal[2]*val_velocity[2]) / *val_density+ dp_drho/rhoxc;
    val_invp_tensor[3][1]=val_normal[0] / *val_density - val_velocity[0]*k_o_rhoxc;
    val_invp_tensor[3][2]=val_normal[1] / *val_density- val_velocity[1]*k_o_rhoxc;
    val_invp_tensor[3][3]=val_normal[2] / *val_density- val_velocity[2]*k_o_rhoxc;
    val_invp_tensor[3][4]= k_o_rhoxc;

    val_invp_tensor[4][0]=(val_normal[0]*val_velocity[0]+val_normal[1]*val_velocity[1]+val_normal[2]*val_velocity[2]) / *val_density+ dp_drho/rhoxc;
    val_invp_tensor[4][1]=-val_normal[0] / *val_density- val_velocity[0]*k_o_rhoxc;
    val_invp_tensor[4][2]=-val_normal[1] / *val_density- val_velocity[1]*k_o_rhoxc;
    val_invp_tensor[4][3]=-val_normal[2] / *val_density- val_velocity[2]*k_o_rhoxc;
    val_invp_tensor[4][4]= k_o_rhoxc;
  }
  if (nDim == 2) {
    sqvel = val_velocity[0]*val_velocity[0]+val_velocity[1]*val_velocity[1];
    dp_drho = *val_chi + 0.5*sqvel*(*val_kappa);

    val_invp_tensor[0][0] = 1.0 - dp_drho/c2;
    val_invp_tensor[0][1]= k_o_c2*val_velocity[0];
    val_invp_tensor[0][2]= k_o_c2*val_velocity[1];
    val_invp_tensor[0][3]=-k_o_c2;

    val_invp_tensor[1][0]=-k1orho*val_velocity[0]+k0orho*val_velocity[1];
    val_invp_tensor[1][1]=k1orho;
    val_invp_tensor[1][2]=-k0orho;
    val_invp_tensor[1][3]=0.0;

    val_invp_tensor[2][0]=-k0orho*val_velocity[0]-k1orho*val_velocity[1] + dp_drho/rhoxc;
    val_invp_tensor[2][1]=k0orho - k_o_rhoxc*val_velocity[0];
    val_invp_tensor[2][2]=k1orho - k_o_rhoxc*val_velocity[1];
    val_invp_tensor[2][3]=k_o_rhoxc;

    val_invp_tensor[3][0]=k0orho*val_velocity[0]+k1orho*val_velocity[1] + dp_drho/rhoxc;
    val_invp_tensor[3][1]=-k0orho - k_o_rhoxc*val_velocity[0];
    val_invp_tensor[3][2]=-k1orho - k_o_rhoxc*val_velocity[1];
    val_invp_tensor[3][3]= k_o_rhoxc;
  }
}

void CNumerics::GetPMatrix_inv(su2double *U, su2double *V, su2double *val_dPdU,
                               su2double *val_normal, su2double *l, su2double *m,
                               su2double **val_invp_tensor) {

  unsigned short iSpecies, jSpecies, iDim, iVar, jVar;
  su2double rho, a, a2, eve;
  su2double vU, vV, vW;

  for (iVar = 0; iVar < nVar; iVar++)
    for (jVar = 0; jVar < nVar; jVar++)
      val_invp_tensor[iVar][jVar] = 0.0;

  /*--- Pre-compute useful quantities ---*/
  rho = V[RHO_INDEX];
  eve = U[nSpecies+nDim+1]/rho;
  vU = 0.0;  vV = 0.0;  vW = 0.0;
  for (iDim = 0; iDim < nDim; iDim++) {
    vU += V[VEL_INDEX+iDim] * val_normal[iDim];
    vV += V[VEL_INDEX+iDim] * l[iDim];
    vW += V[VEL_INDEX+iDim] * m[iDim];
  }
  a  = V[A_INDEX];
  a2 = V[A_INDEX]*V[A_INDEX];

	if (nDim == 3) {

    for (iSpecies = 0; iSpecies < nSpecies; iSpecies++) {
      for (jSpecies = 0; jSpecies < nSpecies; jSpecies++) {
        val_invp_tensor[iSpecies][jSpecies] = -(V[RHOS_INDEX+iSpecies]/rho) * val_dPdU[jSpecies];
      }
      val_invp_tensor[iSpecies][iSpecies]  += a2;
      val_invp_tensor[iSpecies][nSpecies]   = val_dPdU[nSpecies+nDim] * V[VEL_INDEX] * (V[RHOS_INDEX+iSpecies]/rho);
      val_invp_tensor[iSpecies][nSpecies+1] = val_dPdU[nSpecies+nDim] * V[VEL_INDEX+1] * (V[RHOS_INDEX+iSpecies]/rho);
      val_invp_tensor[iSpecies][nSpecies+2] = val_dPdU[nSpecies+nDim] * V[VEL_INDEX+2] * (V[RHOS_INDEX+iSpecies]/rho);
      val_invp_tensor[iSpecies][nSpecies+3] = -val_dPdU[nSpecies+nDim] * (V[RHOS_INDEX+iSpecies]/rho);
      val_invp_tensor[iSpecies][nSpecies+4] = -val_dPdU[nSpecies+nDim+1] * (V[RHOS_INDEX+iSpecies]/rho);

      val_invp_tensor[nSpecies][iSpecies]   = -vV;
      val_invp_tensor[nSpecies+1][iSpecies] = -vW;
      val_invp_tensor[nSpecies+2][iSpecies] = val_dPdU[iSpecies] - vU*a;
      val_invp_tensor[nSpecies+3][iSpecies] = val_dPdU[iSpecies] + vU*a;
      val_invp_tensor[nSpecies+4][iSpecies] = -eve * val_dPdU[iSpecies];
    }

    val_invp_tensor[nSpecies][nSpecies]     = l[0];
    val_invp_tensor[nSpecies][nSpecies+1]   = l[1];
    val_invp_tensor[nSpecies][nSpecies+2]   = l[2];
    val_invp_tensor[nSpecies][nSpecies+3]   = 0.0;
    val_invp_tensor[nSpecies][nSpecies+4]   = 0.0;

    val_invp_tensor[nSpecies+1][nSpecies]   = m[0];
    val_invp_tensor[nSpecies+1][nSpecies+1] = m[1];
    val_invp_tensor[nSpecies+1][nSpecies+2] = m[2];
    val_invp_tensor[nSpecies+1][nSpecies+3] = 0.0;
    val_invp_tensor[nSpecies+1][nSpecies+4] = 0.0;

    val_invp_tensor[nSpecies+2][nSpecies]   = a*val_normal[0] - val_dPdU[nSpecies+nDim]*V[VEL_INDEX];
    val_invp_tensor[nSpecies+2][nSpecies+1] = a*val_normal[1] - val_dPdU[nSpecies+nDim]*V[VEL_INDEX+1];
    val_invp_tensor[nSpecies+2][nSpecies+2] = a*val_normal[2] - val_dPdU[nSpecies+nDim]*V[VEL_INDEX+2];
    val_invp_tensor[nSpecies+2][nSpecies+3] = val_dPdU[nSpecies+nDim];
    val_invp_tensor[nSpecies+2][nSpecies+4] = val_dPdU[nSpecies+nDim+1];

    val_invp_tensor[nSpecies+3][nSpecies]   = -a*val_normal[0] - val_dPdU[nSpecies+nDim]*V[VEL_INDEX];
    val_invp_tensor[nSpecies+3][nSpecies+1] = -a*val_normal[1] - val_dPdU[nSpecies+nDim]*V[VEL_INDEX+1];
    val_invp_tensor[nSpecies+3][nSpecies+2] = -a*val_normal[2] - val_dPdU[nSpecies+nDim]*V[VEL_INDEX+2];
    val_invp_tensor[nSpecies+3][nSpecies+3] = val_dPdU[nSpecies+nDim];
    val_invp_tensor[nSpecies+3][nSpecies+4] = val_dPdU[nSpecies+nDim+1];

    val_invp_tensor[nSpecies+4][nSpecies]   = val_dPdU[nSpecies+nDim] * V[VEL_INDEX] * eve;
    val_invp_tensor[nSpecies+4][nSpecies+1] = val_dPdU[nSpecies+nDim] * V[VEL_INDEX+1] * eve;
    val_invp_tensor[nSpecies+4][nSpecies+2] = val_dPdU[nSpecies+nDim] * V[VEL_INDEX+2] * eve;
    val_invp_tensor[nSpecies+4][nSpecies+3] = -val_dPdU[nSpecies+nDim] * eve;
    val_invp_tensor[nSpecies+4][nSpecies+4] = a2 - val_dPdU[nSpecies+nDim+1]*eve;
  }
	if(nDim == 2) {
		cout << "InvP matrix not implemented for 2D flows!!!!" << endl;
	}
}

void CNumerics::GetinvRinvPe(su2double Beta2, su2double val_enthalpy,
                             su2double val_soundspeed, su2double val_density,
                             su2double* val_velocity, su2double **invRinvPe) {

  su2double sqvel;
  su2double factor = 1.0/(val_soundspeed*val_soundspeed*Beta2);

  if (nDim == 2) {

    sqvel = val_velocity[0]*val_velocity[0]+val_velocity[1]*val_velocity[1];

    invRinvPe[0][0] = factor;
    invRinvPe[0][1] = 0.0;
    invRinvPe[0][2] = 0.0;
    invRinvPe[0][3] = -val_density/Gamma;

    invRinvPe[1][0] = val_velocity[0]*factor;
    invRinvPe[1][1] = val_density;
    invRinvPe[1][2] = 0.0;
    invRinvPe[1][3] = -val_density*val_velocity[0]/Gamma;

    invRinvPe[2][0] = val_velocity[1]*factor;
    invRinvPe[2][1] = 0;
    invRinvPe[2][2] = val_density;
    invRinvPe[2][3] = -val_density*val_velocity[1]/Gamma;

    invRinvPe[3][0] = val_enthalpy*factor;
    invRinvPe[3][1] = val_density*val_velocity[0];
    invRinvPe[3][2] = val_density*val_velocity[1];
    invRinvPe[3][3] = -val_density*sqvel/(2.0*Gamma);
  }
  else {

    sqvel = val_velocity[0]*val_velocity[0]+val_velocity[1]*val_velocity[1]+val_velocity[2]*val_velocity[2];

    invRinvPe[0][0] =  factor;
    invRinvPe[0][1] = 0.0;
    invRinvPe[0][2] = 0.0;
    invRinvPe[0][3] = 0.0;
    invRinvPe[0][4] = -val_density/Gamma;

    invRinvPe[1][0] = val_velocity[0]*factor;
    invRinvPe[1][1] = val_density;
    invRinvPe[1][2] = 0.0;
    invRinvPe[1][3] = 0.0;
    invRinvPe[1][4] = -val_density*val_velocity[0]/Gamma;

    invRinvPe[2][0] = val_velocity[1]*factor;
    invRinvPe[2][1] = 0;
    invRinvPe[2][2] = val_density;
    invRinvPe[2][3] = 0.0;
    invRinvPe[2][4] = -val_density*val_velocity[1]/Gamma;


    invRinvPe[3][0] = val_velocity[2]*factor;
    invRinvPe[3][1] = 0;
    invRinvPe[3][2] = 0;
    invRinvPe[3][3] = val_density;
    invRinvPe[3][4] = -val_density*val_velocity[2]/Gamma;

    invRinvPe[4][0] = val_enthalpy*factor;
    invRinvPe[4][1] = val_density*val_velocity[0];
    invRinvPe[4][2] = val_density*val_velocity[1];
    invRinvPe[4][3] = val_density*val_velocity[2];
    invRinvPe[4][4] = -val_density*sqvel/(2.0*Gamma);

  }

}

void CNumerics::GetRMatrix(su2double val_pressure, su2double val_soundspeed, su2double val_density, su2double* val_velocity, su2double **R_Matrix) {

  su2double sqvel;
  //su2double factor = 1.0/(val_soundspeed*val_soundspeed*1);
  su2double gm1 = Gamma - 1.0;

  if (nDim == 2) {

    sqvel = val_velocity[0]*val_velocity[0]+val_velocity[1]*val_velocity[1];

    R_Matrix[0][0] =  0.5*gm1*sqvel;
    R_Matrix[0][1] = -val_velocity[0]*gm1;
    R_Matrix[0][2] = -val_velocity[1]*gm1;
    R_Matrix[0][3] = gm1;

    R_Matrix[1][0] = -val_velocity[0]/val_density;
    R_Matrix[1][1] = 1.0/val_density;
    R_Matrix[1][2] = 0.0;
    R_Matrix[1][3] = 0.0;

    R_Matrix[2][0] = -val_velocity[1]/val_density;
    R_Matrix[2][1] = 0.0;
    R_Matrix[2][2] = 1.0/val_density;
    R_Matrix[2][3] = 0.0;

    R_Matrix[3][0] = 0.5*gm1*sqvel/val_pressure - Gamma/val_density;
    R_Matrix[3][1] = -gm1*val_velocity[0]/val_pressure;
    R_Matrix[3][2] = -gm1*val_velocity[1]/val_pressure;
    R_Matrix[3][3] = gm1/val_pressure;
  }
  else {

    sqvel = val_velocity[0]*val_velocity[0]+val_velocity[1]*val_velocity[1]+val_velocity[2]*val_velocity[2];

    R_Matrix[0][0] =  0.5*gm1*sqvel;
    R_Matrix[0][1] = -val_velocity[0]*gm1;
    R_Matrix[0][2] = -val_velocity[1]*gm1;
    R_Matrix[0][3] = -val_velocity[2]*gm1;
    R_Matrix[0][4] = gm1;

    R_Matrix[1][0] = -val_velocity[0]/val_density;
    R_Matrix[1][1] = 1.0/val_density;
    R_Matrix[1][2] = 0.0;
    R_Matrix[1][3] = 0.0;
    R_Matrix[1][4] = 0.0;

    R_Matrix[2][0] = -val_velocity[1]/val_density;
    R_Matrix[2][1] = 0.0;
    R_Matrix[2][2] = 1.0/val_density;
    R_Matrix[2][3] = 0.0;
    R_Matrix[2][4] = 0.0;

    R_Matrix[3][0] = -val_velocity[2]/val_density;
    R_Matrix[3][1] = 0.0;
    R_Matrix[3][2] = 0.0;
    R_Matrix[3][3] = 1.0/val_density;
    R_Matrix[3][4] = 0.0;

    R_Matrix[4][0] = 0.5*gm1*sqvel/val_pressure - Gamma/val_density;
    R_Matrix[4][1] = -gm1*val_velocity[0]/val_pressure;
    R_Matrix[4][2] = -gm1*val_velocity[1]/val_pressure;
    R_Matrix[4][3] = -gm1*val_velocity[2]/val_pressure;
    R_Matrix[4][4] = gm1/val_pressure;

  }

}

void CNumerics::GetRMatrix(su2double val_soundspeed, su2double val_density, su2double **R_Matrix) {

  su2double cc, rhoc;
  cc = val_soundspeed*val_soundspeed;
  rhoc = val_density*val_soundspeed;
  if (nDim == 2) {
    R_Matrix[0][0] = -1.0/cc;
    R_Matrix[0][1] = 0.0;
    R_Matrix[0][2] = 0.5/cc;
    R_Matrix[0][3] = 0.5/cc;

    R_Matrix[1][0] = 0.0;
    R_Matrix[1][1] = 0.0;
    R_Matrix[1][2] = 0.5/rhoc;
    R_Matrix[1][3] = -0.5/rhoc;

    R_Matrix[2][0] = 0.0;
    R_Matrix[2][1] = 1.0/rhoc;
    R_Matrix[2][2] = 0.0;
    R_Matrix[2][3] = 0.0;

    R_Matrix[3][0] = 0.0;
    R_Matrix[3][1] = 0.0;
    R_Matrix[3][2] = 0.5;
    R_Matrix[3][3] = 0.5;

  }
  else {

    R_Matrix[0][0] = -1.0/cc;
    R_Matrix[0][1] = 0.0;
    R_Matrix[0][2] = 0.0;
    R_Matrix[0][3] = 0.5/cc;
    R_Matrix[0][4] = 0.5/cc;

    R_Matrix[1][0] = 0.0;
    R_Matrix[1][1] = 0.0;
    R_Matrix[1][2] = 0.0;
    R_Matrix[1][3] = 0.5/rhoc;
    R_Matrix[1][4] = -0.5/rhoc;

    R_Matrix[2][0] = 0.0;
    R_Matrix[2][1] = 1.0/rhoc;
    R_Matrix[2][2] = 0.0;
    R_Matrix[2][3] = 0.0;
    R_Matrix[2][4] = 0.0;

    R_Matrix[3][0] = 0.0;
    R_Matrix[3][1] = 0.0;
    R_Matrix[3][2] = 1.0/rhoc;
    R_Matrix[3][3] = 0.0;
    R_Matrix[3][4] = 0.0;

    R_Matrix[4][0] = 0.0;
    R_Matrix[4][1] = 0.0;
    R_Matrix[4][2] = 0.0;
    R_Matrix[4][3] = 0.5;
    R_Matrix[4][4] = 0.5;

}

}

void CNumerics::GetLMatrix(su2double val_soundspeed, su2double val_density, su2double **L_Matrix) {

  su2double cc, rhoc;
  cc = val_soundspeed*val_soundspeed;
  rhoc = val_density*val_soundspeed;
  if (nDim == 2) {

    L_Matrix[0][0] = -cc;
    L_Matrix[0][1] = 0.0;
    L_Matrix[0][2] = 0.0;
    L_Matrix[0][3] = 1.0;

    L_Matrix[1][0] = 0.0;
    L_Matrix[1][1] = 0.0;
    L_Matrix[1][2] = rhoc;
    L_Matrix[1][3] = 0.0;

    L_Matrix[2][0] = 0.0;
    L_Matrix[2][1] = rhoc;
    L_Matrix[2][2] = 0.0;
    L_Matrix[2][3] = 1.0;

    L_Matrix[3][0] = 0.0;
    L_Matrix[3][1] = -rhoc;
    L_Matrix[3][2] = 0.0;
    L_Matrix[3][3] = 1.0;
  }
  else {

    L_Matrix[0][0] = -cc;
    L_Matrix[0][1] = 0.0;
    L_Matrix[0][2] = 0.0;
    L_Matrix[0][3] = 0.0;
    L_Matrix[0][4] = 1.0;

    L_Matrix[1][0] = 0.0;
    L_Matrix[1][1] = 0.0;
    L_Matrix[1][2] = rhoc;
    L_Matrix[1][3] = 0.0;
    L_Matrix[1][4] = 0.0;

    L_Matrix[2][0] = 0.0;
    L_Matrix[2][1] = 0.0;
    L_Matrix[2][2] = 0.0;
    L_Matrix[2][3] = rhoc;
    L_Matrix[2][4] = 0.0;

    L_Matrix[3][0] = 0.0;
    L_Matrix[3][1] = rhoc;
    L_Matrix[3][2] = 0.0;
    L_Matrix[3][3] = 0.0;
    L_Matrix[3][4] = 1.0;

    L_Matrix[4][0] = 0.0;
    L_Matrix[4][1] = -rhoc;
    L_Matrix[4][2] = 0.0;
    L_Matrix[4][3] = 0.0;
    L_Matrix[4][4] = 1.0;

  }

}

void CNumerics::ComputeResJacobianGiles(CFluidModel *FluidModel, su2double pressure, su2double density, su2double *turboVel, su2double alphaInBC, su2double gammaInBC,  su2double **R_c, su2double **R_c_inv){
  su2double rhoc, cc;
  su2double dhdrho_P, dhdP_rho, dsdrho_P,dsdP_rho;

  FluidModel->ComputeDerivativeNRBC_Prho(pressure, density);
  cc   = FluidModel->GetSoundSpeed2();
  rhoc = density*sqrt(cc);


  dhdrho_P  = FluidModel->Getdhdrho_P();
  dhdP_rho  = FluidModel->GetdhdP_rho();
  dsdrho_P  = FluidModel->Getdsdrho_P();
  dsdP_rho  = FluidModel->GetdsdP_rho();

  if (nDim == 2){

    R_c[0][0] = -1/cc*dsdrho_P;                   //a11
    R_c[0][1] = 0.0;                                //a12
    R_c[0][2] = 0.5/cc*dsdrho_P + 0.5*dsdP_rho;    //a13

    R_c[1][0] = 0.0;                                //a21
    R_c[1][1] = 1/rhoc;                           //a22
    R_c[1][2] = -0.5/rhoc*tan(alphaInBC);          //a23

    R_c[2][0] = -1/cc*dhdrho_P;                                //a31
    R_c[2][1] = turboVel[1]/rhoc;                                       //a32
    R_c[2][2] = 0.5/cc*dhdrho_P + 0.5*turboVel[0]/rhoc + 0.5*dhdP_rho;  //a33

    InvMatrix3D(R_c, R_c_inv);
  }
  else{
    R_c[0][0] = -1/cc*dsdrho_P;                     //a11
    R_c[0][1] = 0.0;                                //a12
    R_c[0][2] = 0.0;                                //a13
    R_c[0][3] = 0.5/cc*dsdrho_P + 0.5*dsdP_rho;     //a14

    R_c[1][0] = 0.0;                                //a21
    R_c[1][1] = 1/rhoc;                             //a22
    R_c[1][2] = 0.0;                                //a23
    R_c[1][3] = -0.5/rhoc*tan(alphaInBC);           //a24

    R_c[2][0] = 0.0;                                //a31
    R_c[2][1] = 0.0;                                //a32
    R_c[2][2] = 1/rhoc;                             //a33
    R_c[2][3] = -0.5/rhoc*tan(gammaInBC);           //a34

    R_c[3][0] = -1/cc*dhdrho_P;                                          //a41
    R_c[3][1] = turboVel[1]/rhoc;                                        //a42
    R_c[3][2] = turboVel[2]/rhoc;                                        //a43
    R_c[3][3] = 0.5/cc*dhdrho_P + 0.5*turboVel[0]/rhoc + 0.5*dhdP_rho;   //a44

    InvMatrix4D(R_c, R_c_inv);
  }
}

void CNumerics::InvMatrix3D(su2double **matrix, su2double **invMatrix){

  su2double invDet;

  invDet = 1 /
      (- matrix[0][2]*matrix[1][1]*matrix[2][0] + matrix[0][1]*matrix[1][2]*matrix[2][0] + matrix[0][2]*matrix[1][0]*matrix[2][1] -
         matrix[0][0]*matrix[1][2]*matrix[2][1] - matrix[0][1]*matrix[1][0]*matrix[2][2] + matrix[0][0]*matrix[1][1]*matrix[2][2]);

  invMatrix[0][0] = invDet*( - matrix[1][2]*matrix[2][1] + matrix[1][1]*matrix[2][2] );
  invMatrix[0][1] = invDet*( + matrix[0][2]*matrix[2][1] - matrix[0][1]*matrix[2][2] );
  invMatrix[0][2] = invDet*( - matrix[0][2]*matrix[1][1] + matrix[0][1]*matrix[1][2] );

  invMatrix[1][0] = invDet*( + matrix[1][2]*matrix[2][0] - matrix[1][0]*matrix[2][2] );
  invMatrix[1][1] = invDet*( - matrix[0][2]*matrix[2][0] + matrix[0][0]*matrix[2][2] );
  invMatrix[1][2] = invDet*( + matrix[0][2]*matrix[1][0] - matrix[0][0]*matrix[1][2] );

  invMatrix[2][0] = invDet*( - matrix[1][1]*matrix[2][0] + matrix[1][0]*matrix[2][1] );
  invMatrix[2][1] = invDet*( + matrix[0][1]*matrix[2][0] - matrix[0][0]*matrix[2][1] );
  invMatrix[2][2] = invDet*( - matrix[0][1]*matrix[1][0] + matrix[0][0]*matrix[1][1] );

}

void CNumerics::InvMatrix4D(su2double **matrix, su2double **invMatrix){
  su2double invDet;

  invDet = 1 /
      (matrix[0][3]*matrix[1][2]*matrix[2][1]*matrix[3][0] - matrix[0][2]*matrix[1][3]*matrix[2][1]*matrix[3][0] - matrix[0][3]*matrix[1][1]*matrix[2][2]*matrix[3][0] +
          matrix[0][1]*matrix[1][3]*matrix[2][2]*matrix[3][0] + matrix[0][2]*matrix[1][1]*matrix[2][3]*matrix[3][0] - matrix[0][1]*matrix[1][2]*matrix[2][3]*matrix[3][0] -
          matrix[0][3]*matrix[1][2]*matrix[2][0]*matrix[3][1] + matrix[0][2]*matrix[1][3]*matrix[2][0]*matrix[3][1] + matrix[0][3]*matrix[1][0]*matrix[2][2]*matrix[3][1] -
          matrix[0][0]*matrix[1][3]*matrix[2][2]*matrix[3][1] - matrix[0][2]*matrix[1][0]*matrix[2][3]*matrix[3][1] + matrix[0][0]*matrix[1][2]*matrix[2][3]*matrix[3][1] +
          matrix[0][3]*matrix[1][1]*matrix[2][0]*matrix[3][2] - matrix[0][1]*matrix[1][3]*matrix[2][0]*matrix[3][2] - matrix[0][3]*matrix[1][0]*matrix[2][1]*matrix[3][2] +
          matrix[0][0]*matrix[1][3]*matrix[2][1]*matrix[3][2] + matrix[0][1]*matrix[1][0]*matrix[2][3]*matrix[3][2] - matrix[0][0]*matrix[1][1]*matrix[2][3]*matrix[3][2] -
          matrix[0][2]*matrix[1][1]*matrix[2][0]*matrix[3][3] + matrix[0][1]*matrix[1][2]*matrix[2][0]*matrix[3][3] + matrix[0][2]*matrix[1][0]*matrix[2][1]*matrix[3][3] -
          matrix[0][0]*matrix[1][2]*matrix[2][1]*matrix[3][3] - matrix[0][1]*matrix[1][0]*matrix[2][2]*matrix[3][3] + matrix[0][0]*matrix[1][1]*matrix[2][2]*matrix[3][3]);

  invMatrix[0][0] = invDet*(- matrix[1][3]*matrix[2][2]*matrix[3][1] + matrix[1][2]*matrix[2][3]*matrix[3][1] + matrix[1][3]*matrix[2][1]*matrix[3][2] - matrix[1][1]*matrix[2][3]*matrix[3][2] - matrix[1][2]*matrix[2][1]*matrix[3][3] + matrix[1][1]*matrix[2][2]*matrix[3][3]) ;
  invMatrix[0][1] = invDet*(  matrix[0][3]*matrix[2][2]*matrix[3][1] - matrix[0][2]*matrix[2][3]*matrix[3][1] - matrix[0][3]*matrix[2][1]*matrix[3][2] + matrix[0][1]*matrix[2][3]*matrix[3][2] + matrix[0][2]*matrix[2][1]*matrix[3][3] - matrix[0][1]*matrix[2][2]*matrix[3][3]) ;
  invMatrix[0][2] = invDet*(- matrix[0][3]*matrix[1][2]*matrix[3][1] + matrix[0][2]*matrix[1][3]*matrix[3][1] + matrix[0][3]*matrix[1][1]*matrix[3][2] - matrix[0][1]*matrix[1][3]*matrix[3][2] - matrix[0][2]*matrix[1][1]*matrix[3][3] + matrix[0][1]*matrix[1][2]*matrix[3][3]) ;
  invMatrix[0][3] = invDet*(  matrix[0][3]*matrix[1][2]*matrix[2][1] - matrix[0][2]*matrix[1][3]*matrix[2][1] - matrix[0][3]*matrix[1][1]*matrix[2][2] + matrix[0][1]*matrix[1][3]*matrix[2][2] + matrix[0][2]*matrix[1][1]*matrix[2][3] - matrix[0][1]*matrix[1][2]*matrix[2][3]) ;

  invMatrix[1][0] = invDet*(  matrix[1][3]*matrix[2][2]*matrix[3][0] - matrix[1][2]*matrix[2][3]*matrix[3][0] - matrix[1][3]*matrix[2][0]*matrix[3][2] + matrix[1][0]*matrix[2][3]*matrix[3][2] + matrix[1][2]*matrix[2][0]*matrix[3][3] - matrix[1][0]*matrix[2][2]*matrix[3][3]) ;
  invMatrix[1][1] = invDet*(- matrix[0][3]*matrix[2][2]*matrix[3][0] + matrix[0][2]*matrix[2][3]*matrix[3][0] + matrix[0][3]*matrix[2][0]*matrix[3][2] - matrix[0][0]*matrix[2][3]*matrix[3][2] - matrix[0][2]*matrix[2][0]*matrix[3][3] + matrix[0][0]*matrix[2][2]*matrix[3][3]) ;
  invMatrix[1][2] = invDet*(  matrix[0][3]*matrix[1][2]*matrix[3][0] - matrix[0][2]*matrix[1][3]*matrix[3][0] - matrix[0][3]*matrix[1][0]*matrix[3][2] + matrix[0][0]*matrix[1][3]*matrix[3][2] + matrix[0][2]*matrix[1][0]*matrix[3][3] - matrix[0][0]*matrix[1][2]*matrix[3][3]) ;
  invMatrix[1][3] = invDet*(- matrix[0][3]*matrix[1][2]*matrix[2][0] + matrix[0][2]*matrix[1][3]*matrix[2][0] + matrix[0][3]*matrix[1][0]*matrix[2][2] - matrix[0][0]*matrix[1][3]*matrix[2][2] - matrix[0][2]*matrix[1][0]*matrix[2][3] + matrix[0][0]*matrix[1][2]*matrix[2][3]) ;

  invMatrix[2][0] = invDet*(- matrix[1][3]*matrix[2][1]*matrix[3][0] + matrix[1][1]*matrix[2][3]*matrix[3][0] + matrix[1][3]*matrix[2][0]*matrix[3][1] - matrix[1][0]*matrix[2][3]*matrix[3][1] - matrix[1][1]*matrix[2][0]*matrix[3][3] + matrix[1][0]*matrix[2][1]*matrix[3][3]) ;
  invMatrix[2][1] = invDet*(  matrix[0][3]*matrix[2][1]*matrix[3][0] - matrix[0][1]*matrix[2][3]*matrix[3][0] - matrix[0][3]*matrix[2][0]*matrix[3][1] + matrix[0][0]*matrix[2][3]*matrix[3][1] + matrix[0][1]*matrix[2][0]*matrix[3][3] - matrix[0][0]*matrix[2][1]*matrix[3][3]) ;
  invMatrix[2][2] = invDet*(- matrix[0][3]*matrix[1][1]*matrix[3][0] + matrix[0][1]*matrix[1][3]*matrix[3][0] + matrix[0][3]*matrix[1][0]*matrix[3][1] - matrix[0][0]*matrix[1][3]*matrix[3][1] - matrix[0][1]*matrix[1][0]*matrix[3][3] + matrix[0][0]*matrix[1][1]*matrix[3][3]) ;
  invMatrix[2][3] = invDet*(  matrix[0][3]*matrix[1][1]*matrix[2][0] - matrix[0][1]*matrix[1][3]*matrix[2][0] - matrix[0][3]*matrix[1][0]*matrix[2][1] + matrix[0][0]*matrix[1][3]*matrix[2][1] + matrix[0][1]*matrix[1][0]*matrix[2][3] - matrix[0][0]*matrix[1][1]*matrix[2][3]) ;

  invMatrix[3][0] = invDet*(  matrix[1][2]*matrix[2][1]*matrix[3][0] - matrix[1][1]*matrix[2][2]*matrix[3][0] - matrix[1][2]*matrix[2][0]*matrix[3][1] + matrix[1][0]*matrix[2][2]*matrix[3][1] + matrix[1][1]*matrix[2][0]*matrix[3][2] - matrix[1][0]*matrix[2][1]*matrix[3][2]) ;
  invMatrix[3][1] = invDet*(- matrix[0][2]*matrix[2][1]*matrix[3][0] + matrix[0][1]*matrix[2][2]*matrix[3][0] + matrix[0][2]*matrix[2][0]*matrix[3][1] - matrix[0][0]*matrix[2][2]*matrix[3][1] - matrix[0][1]*matrix[2][0]*matrix[3][2] + matrix[0][0]*matrix[2][1]*matrix[3][2]) ;
  invMatrix[3][2] = invDet*(  matrix[0][2]*matrix[1][1]*matrix[3][0] - matrix[0][1]*matrix[1][2]*matrix[3][0] - matrix[0][2]*matrix[1][0]*matrix[3][1] + matrix[0][0]*matrix[1][2]*matrix[3][1] + matrix[0][1]*matrix[1][0]*matrix[3][2] - matrix[0][0]*matrix[1][1]*matrix[3][2]) ;
  invMatrix[3][3] = invDet*(- matrix[0][2]*matrix[1][1]*matrix[2][0] + matrix[0][1]*matrix[1][2]*matrix[2][0] + matrix[0][2]*matrix[1][0]*matrix[2][1] - matrix[0][0]*matrix[1][2]*matrix[2][1] - matrix[0][1]*matrix[1][0]*matrix[2][2] + matrix[0][0]*matrix[1][1]*matrix[2][2]) ;


}

void CNumerics::GetCharJump(su2double val_soundspeed, su2double val_density, su2double *delta_prim, su2double *delta_char){

  su2double cc, rhoc;
  cc = val_soundspeed*val_soundspeed;
  rhoc = val_density*val_soundspeed;
  if (nDim == 2) {
    delta_char[0] = -cc*delta_prim[0] + delta_prim[3];
    delta_char[1] = rhoc*delta_prim[2];
    delta_char[2] = rhoc*delta_prim[1] + delta_prim[3];																	;
    delta_char[3] = -rhoc*delta_prim[1] + delta_prim[3];
  }else {
    delta_char[0] = -cc*delta_prim[0] + delta_prim[4];
    delta_char[1] = rhoc*delta_prim[2];
    delta_char[2] = rhoc*delta_prim[3];
    delta_char[3] = rhoc*delta_prim[1] + delta_prim[4];
    delta_char[4] = -rhoc*delta_prim[1] + delta_prim[4];
  }
}

void CNumerics::GetPrecondJacobian(su2double Beta2, su2double r_hat, su2double s_hat, su2double t_hat, su2double rB2a2, su2double* Lambda, su2double *val_normal,
    su2double **val_absPeJac) {

  su2double lam1, lam2, lam3, lam4;
  lam1 = Lambda[0]; lam2 = Lambda[1]; lam3 = Lambda[2]; lam4 = Lambda[3];

  if (nDim == 2) {

    val_absPeJac[0][0] =  lam3*s_hat/(2.0*t_hat) - lam4*r_hat/(2.0*t_hat);
    val_absPeJac[0][1] = -lam3*rB2a2*val_normal[0]/(2.0*t_hat) + lam4*rB2a2*val_normal[0]/(2.0*t_hat);
    val_absPeJac[0][2] = -lam3*rB2a2*val_normal[1]/(2.0*t_hat) + lam4*rB2a2*val_normal[1]/(2.0*t_hat);
    val_absPeJac[0][3] =  0.0;

    val_absPeJac[1][0] = r_hat*val_normal[0]*lam3*s_hat/(2.0*t_hat*rB2a2) + s_hat*val_normal[0]*lam4*(-r_hat)/(2.0*t_hat*rB2a2);
    val_absPeJac[1][1] = lam2*(val_normal[1]*val_normal[1]) - lam3*r_hat*val_normal[0]*val_normal[0]/(2.0*t_hat) + lam4*s_hat*val_normal[0]*val_normal[0]/(2.0*t_hat);
    val_absPeJac[1][2] = -lam2*val_normal[0]*val_normal[1] - lam3*r_hat*val_normal[0]*val_normal[1]/(2.0*t_hat) + lam4*s_hat*val_normal[0]*val_normal[1]/(2.0*t_hat);
    val_absPeJac[1][3] = 0.0;

    val_absPeJac[2][0] = lam3*r_hat*val_normal[1]*s_hat/(2.0*t_hat*rB2a2) - s_hat*val_normal[1]*lam4*r_hat/(2.0*t_hat*rB2a2);
    val_absPeJac[2][1] = -val_normal[0]*val_normal[1]*lam2 - r_hat*val_normal[1]*val_normal[0]*lam3/(2.0*t_hat) + s_hat*val_normal[0]*val_normal[1]*lam4/(2.0*t_hat);
    val_absPeJac[2][2] = val_normal[0]*val_normal[0]*lam2 -r_hat*val_normal[1]*val_normal[1]*lam3/(2.0*t_hat) + s_hat*val_normal[1]*val_normal[1]*lam4/(2.0*t_hat);
    val_absPeJac[2][3] = 0.0;

    val_absPeJac[3][0] = 0.0;
    val_absPeJac[3][1] = 0.0;
    val_absPeJac[3][2] = 0.0;
    val_absPeJac[3][3] = lam1;

  }
  else {

    su2double lam5 = Lambda[4];

    val_absPeJac[0][0] =  lam4*s_hat/(2.0*t_hat) - lam5*r_hat/(2.0*t_hat);
    val_absPeJac[0][1] = -lam4*rB2a2*val_normal[0]/(2.0*t_hat) + lam5*rB2a2*val_normal[0]/(2.0*t_hat);
    val_absPeJac[0][2] = -lam4*rB2a2*val_normal[1]/(2.0*t_hat) + lam5*rB2a2*val_normal[1]/(2.0*t_hat);
    val_absPeJac[0][3] = -lam4*rB2a2*val_normal[2]/(2.0*t_hat) + lam5*rB2a2*val_normal[2]/(2.0*t_hat);
    val_absPeJac[0][4] =  0.0;

    val_absPeJac[1][0] = r_hat*val_normal[0]*lam4*s_hat/(2.0*t_hat*rB2a2) + s_hat*val_normal[0]*lam5*(-r_hat)/(2.0*t_hat*rB2a2);
    val_absPeJac[1][1] = lam2*(val_normal[2]*val_normal[2] + val_normal[1]*val_normal[1]) - lam4*r_hat*val_normal[0]*val_normal[0]/(2.0*t_hat) + lam5*s_hat*val_normal[0]*val_normal[0]/(2.0*t_hat);
    val_absPeJac[1][2] = -lam2*val_normal[0]*val_normal[1] - lam4*r_hat*val_normal[0]*val_normal[1]/(2.0*t_hat) + lam5*s_hat*val_normal[0]*val_normal[1]/(2.0*t_hat);
    val_absPeJac[1][3] = -lam2*val_normal[0]*val_normal[2] - lam4*r_hat*val_normal[0]*val_normal[2]/(2.0*t_hat) + lam5*s_hat*val_normal[0]*val_normal[2]/(2.0*t_hat);
    val_absPeJac[1][4] = 0.0;

    val_absPeJac[2][0] = lam4*r_hat*val_normal[1]*s_hat/(2.0*t_hat*rB2a2) - s_hat*val_normal[1]*lam5*r_hat/(2.0*t_hat*rB2a2);
    val_absPeJac[2][1] = -val_normal[0]*val_normal[1]*lam2 - r_hat*val_normal[1]*val_normal[0]*lam4/(2.0*t_hat) + s_hat*val_normal[0]*val_normal[1]*lam5/(2.0*t_hat);
    val_absPeJac[2][2] = val_normal[0]*val_normal[0]*lam2 + val_normal[2]*val_normal[2]*lam3 -r_hat*val_normal[1]*val_normal[1]*lam4/(2.0*t_hat) + s_hat*val_normal[1]*val_normal[1]*lam5/(2.0*t_hat);
    val_absPeJac[2][3] = -val_normal[2]*val_normal[1]*lam2 - r_hat*val_normal[2]*val_normal[1]*lam4/(2.0*t_hat) + s_hat*lam5*val_normal[1]*val_normal[2]/(2.0*t_hat);
    val_absPeJac[2][4] = 0.0;

    val_absPeJac[3][0] = r_hat*s_hat*val_normal[2]*lam4/(2.0*t_hat*rB2a2) - r_hat*s_hat*val_normal[2]*lam5/(2.0*t_hat*rB2a2);
    val_absPeJac[3][1] = -val_normal[0]*val_normal[2]*lam3 - lam4*val_normal[0]*val_normal[2]*r_hat/(2.0*t_hat) + lam5*val_normal[0]*val_normal[2]*s_hat/(2.0*t_hat);
    val_absPeJac[3][2] = -val_normal[1]*val_normal[2]*lam3 - lam4*val_normal[1]*val_normal[2]*r_hat/(2.0*t_hat) + lam5*val_normal[1]*val_normal[2]*s_hat/(2.0*t_hat);
    val_absPeJac[3][3] = (val_normal[1]*val_normal[1] + val_normal[0]*val_normal[0])*lam3 - lam4*val_normal[2]*val_normal[2]*r_hat/(2.0*t_hat) + lam5*val_normal[2]*val_normal[2]*s_hat/(2.0*t_hat);
    val_absPeJac[3][4] = 0.0;

    val_absPeJac[4][0] = 0.0;
    val_absPeJac[4][1] = 0.0;
    val_absPeJac[4][2] = 0.0;
    val_absPeJac[4][3] = 0.0;
    val_absPeJac[4][4] = lam1;

  }

}

void CNumerics::GetJacInviscidLambda_fabs(su2double *val_velocity, su2double val_soundspeed,
    su2double *val_normal, su2double *val_Lambda_Vector) {
  su2double ProjVelocity = 0;

  for (unsigned short iDim = 0; iDim < nDim; iDim++)
    ProjVelocity += val_velocity[iDim]*val_normal[iDim];

  if (nDim == 3) {
    val_Lambda_Vector[0] = fabs(ProjVelocity);
    val_Lambda_Vector[1] = fabs(ProjVelocity);
    val_Lambda_Vector[2] = fabs(ProjVelocity);
    val_Lambda_Vector[3] = fabs(ProjVelocity + val_soundspeed);
    val_Lambda_Vector[4] = fabs(ProjVelocity - val_soundspeed);
  }

  if (nDim == 2) {
    val_Lambda_Vector[0] = fabs(ProjVelocity);
    val_Lambda_Vector[1] = fabs(ProjVelocity);
    val_Lambda_Vector[2] = fabs(ProjVelocity + val_soundspeed);
    val_Lambda_Vector[3] = fabs(ProjVelocity - val_soundspeed);
  }
}

void CNumerics::GetAdjViscousFlux_Jac(su2double Pressure_i, su2double Pressure_j, su2double Density_i, su2double Density_j,
                                      su2double ViscDens_i, su2double ViscDens_j, su2double *Velocity_i, su2double *Velocity_j,
                                      su2double sq_vel_i, su2double sq_vel_j,
                                      su2double XiDens_i, su2double XiDens_j, su2double **Mean_GradPhi, su2double *Mean_GradPsiE,
                                      su2double dPhiE_dn, su2double *Normal, su2double *Edge_Vector, su2double dist_ij_2, su2double *val_residual_i, su2double *val_residual_j,
                                      su2double **val_Jacobian_ii, su2double **val_Jacobian_ij, su2double **val_Jacobian_ji,
                                      su2double **val_Jacobian_jj, bool implicit) {
  
  su2double Sigma_xx, Sigma_yy, Sigma_zz, Sigma_xy, Sigma_xz, Sigma_yz,
  Sigma_xx5, Sigma_yy5, Sigma_zz5, Sigma_xy5, Sigma_xz5,
  Sigma_yz5, Sigma_5, eta_xx, eta_yy, eta_zz, eta_xy, eta_xz, eta_yz;
  su2double dSigmaxx_phi1, dSigmayy_phi1, dSigmazz_phi1, dSigmaxy_phi1, dSigmaxz_phi1, dSigmayz_phi1;
  su2double dSigmaxx_phi2, dSigmayy_phi2, dSigmazz_phi2, dSigmaxy_phi2, dSigmaxz_phi2, dSigmayz_phi2;
  su2double dSigmaxx_phi3, dSigmayy_phi3, dSigmazz_phi3, dSigmaxy_phi3, dSigmaxz_phi3, dSigmayz_phi3;
  su2double dSigma5_psi5;
  unsigned short iVar, jVar;
  
  if (nDim == 3) {
    
    /*--- Residual at iPoint ---*/
    
    Sigma_xx = ViscDens_i * (FOUR3 * Mean_GradPhi[0][0] -  TWO3 * Mean_GradPhi[1][1] - TWO3  * Mean_GradPhi[2][2]);
    Sigma_yy = ViscDens_i * (-TWO3 * Mean_GradPhi[0][0] + FOUR3 * Mean_GradPhi[1][1] - TWO3  * Mean_GradPhi[2][2]);
    Sigma_zz = ViscDens_i * (-TWO3 * Mean_GradPhi[0][0] -  TWO3 * Mean_GradPhi[1][1] + FOUR3 * Mean_GradPhi[2][2]);
    Sigma_xy = ViscDens_i * (Mean_GradPhi[1][0] + Mean_GradPhi[0][1]);
    Sigma_xz = ViscDens_i * (Mean_GradPhi[2][0] + Mean_GradPhi[0][2]);
    Sigma_yz = ViscDens_i * (Mean_GradPhi[2][1] + Mean_GradPhi[1][2]);
    Sigma_xx5 = ViscDens_i * ( FOUR3 * Velocity_i[0] * Mean_GradPsiE[0] -  TWO3 * Velocity_i[1] * Mean_GradPsiE[1] -  TWO3 * Velocity_i[2] * Mean_GradPsiE[2]);
    Sigma_yy5 = ViscDens_i * (- TWO3 * Velocity_i[0] * Mean_GradPsiE[0] + FOUR3 * Velocity_i[1] * Mean_GradPsiE[1] -  TWO3 * Velocity_i[2] * Mean_GradPsiE[2]);
    Sigma_zz5 = ViscDens_i * (- TWO3 * Velocity_i[0] * Mean_GradPsiE[0] -  TWO3 * Velocity_i[1] * Mean_GradPsiE[1] + FOUR3 * Velocity_i[2] * Mean_GradPsiE[2]);
    Sigma_xy5 = ViscDens_i * (Velocity_i[0] * Mean_GradPsiE[1] + Velocity_i[1] * Mean_GradPsiE[0]);
    Sigma_xz5 = ViscDens_i * (Velocity_i[0] * Mean_GradPsiE[2] + Velocity_i[2] * Mean_GradPsiE[0]);
    Sigma_yz5 = ViscDens_i * (Velocity_i[1] * Mean_GradPsiE[2] + Velocity_i[2] * Mean_GradPsiE[1]);
    Sigma_5   = XiDens_i * dPhiE_dn;
    eta_xx = Sigma_xx + Sigma_xx5; eta_yy = Sigma_yy + Sigma_yy5; eta_zz = Sigma_zz + Sigma_zz5;
    eta_xy = Sigma_xy + Sigma_xy5; eta_xz = Sigma_xz + Sigma_xz5; eta_yz = Sigma_yz + Sigma_yz5;
    
    val_residual_i[0] = - (Velocity_i[0] * Normal[0] * eta_xx  + Velocity_i[1] * Normal[1] * eta_yy + Velocity_i[2] * Normal[2] * eta_zz
                           + (Velocity_i[0] * Normal[1] + Velocity_i[1] * Normal[0]) * eta_xy
                           + (Velocity_i[0] * Normal[2] + Velocity_i[2] * Normal[0]) * eta_xz
                           + (Velocity_i[2] * Normal[1] + Velocity_i[1] * Normal[2]) * eta_yz
                           - (sq_vel_i - Pressure_i/(Density_i*Gamma_Minus_One)) * Sigma_5);
    
    val_residual_i[1] = (eta_xx * Normal[0] + eta_xy * Normal[1] + eta_xz * Normal[2] - Velocity_i[0] * Sigma_5);
    val_residual_i[2] = (eta_xy * Normal[0] + eta_yy * Normal[1] + eta_yz * Normal[2] - Velocity_i[1] * Sigma_5);
    val_residual_i[3] = (eta_xz * Normal[0] + eta_yz * Normal[1] + eta_zz * Normal[2] - Velocity_i[2] * Sigma_5);
    val_residual_i[4] = (Sigma_5);
    
    /*--- Computation of the Jacobians at Point i---*/
    
    if (implicit) {
      
      dSigmaxx_phi1 = -FOUR3 * ViscDens_i * Edge_Vector[0]/dist_ij_2;
      dSigmaxx_phi2 =   TWO3 * ViscDens_i * Edge_Vector[1]/dist_ij_2;
      dSigmaxx_phi3 =   TWO3 * ViscDens_i * Edge_Vector[2]/dist_ij_2;
      dSigmayy_phi1 =   TWO3 * ViscDens_i * Edge_Vector[0]/dist_ij_2;
      dSigmayy_phi2 = -FOUR3 * ViscDens_i * Edge_Vector[1]/dist_ij_2;
      dSigmayy_phi3 =   TWO3 * ViscDens_i * Edge_Vector[2]/dist_ij_2;
      dSigmazz_phi1 =   TWO3 * ViscDens_i * Edge_Vector[0]/dist_ij_2;
      dSigmazz_phi2 =   TWO3 * ViscDens_i * Edge_Vector[1]/dist_ij_2;
      dSigmazz_phi3 = -FOUR3 * ViscDens_i * Edge_Vector[2]/dist_ij_2;
      dSigmaxy_phi1 = -ViscDens_i * Edge_Vector[1]/dist_ij_2;
      dSigmaxy_phi2 = -ViscDens_i * Edge_Vector[0]/dist_ij_2;
      dSigmaxy_phi3 = 0;
      dSigmaxz_phi1 = -ViscDens_i * Edge_Vector[2]/dist_ij_2;
      dSigmaxz_phi2 = 0;
      dSigmaxz_phi3 = -ViscDens_i * Edge_Vector[0]/dist_ij_2;
      dSigmayz_phi1 = 0;
      dSigmayz_phi2 = -ViscDens_i * Edge_Vector[2]/dist_ij_2;
      dSigmayz_phi3 = -ViscDens_i * Edge_Vector[1]/dist_ij_2;
      
      //      dSigmaxx5_psi5 = -ViscDens_i * ( FOUR3*Velocity_i[0]*Edge_Vector[0] -  TWO3*Velocity_i[1]*Edge_Vector[1] -  TWO3*Velocity_i[2]*Edge_Vector[2])/dist_ij_2;
      //      dSigmayy5_psi5 = -ViscDens_i * (- TWO3*Velocity_i[0]*Edge_Vector[0] + FOUR3*Velocity_i[1]*Edge_Vector[1] -  TWO3*Velocity_i[2]*Edge_Vector[2])/dist_ij_2;
      //      dSigmazz5_psi5 = -ViscDens_i * (- TWO3*Velocity_i[0]*Edge_Vector[0] -  TWO3*Velocity_i[1]*Edge_Vector[1] + FOUR3*Velocity_i[2]*Edge_Vector[2])/dist_ij_2;
      //      dSigmaxy5_psi5 = -ViscDens_i * ( Velocity_i[0]*Edge_Vector[1] + Velocity_i[1]*Edge_Vector[0] )/dist_ij_2;
      //      dSigmaxz5_psi5 = -ViscDens_i * ( Velocity_i[0]*Edge_Vector[2] + Velocity_i[2]*Edge_Vector[0] )/dist_ij_2;
      //      dSigmayz5_psi5 = -ViscDens_i * ( Velocity_i[1]*Edge_Vector[2] + Velocity_i[2]*Edge_Vector[1] )/dist_ij_2;
      dSigma5_psi5   = -XiDens_i * ( Edge_Vector[0]*Normal[0] + Edge_Vector[1]*Normal[1] + Edge_Vector[2]*Normal[2] )/dist_ij_2;
      
      val_Jacobian_ii[0][0] = 0;
      val_Jacobian_ii[0][1] = -( Velocity_i[0]*Normal[0]*dSigmaxx_phi1 + Velocity_i[1]*Normal[1]*dSigmayy_phi1 + Velocity_i[2]*Normal[2]*dSigmazz_phi1
                                + (Velocity_i[0]*Normal[1] + Velocity_i[1]*Normal[0])*dSigmaxy_phi1
                                + (Velocity_i[0]*Normal[2] + Velocity_i[2]*Normal[0])*dSigmaxz_phi1
                                + (Velocity_i[2]*Normal[1] + Velocity_i[1]*Normal[2])*dSigmayz_phi1 );
      val_Jacobian_ii[0][2] = -( Velocity_i[0]*Normal[0]*dSigmaxx_phi2 + Velocity_i[1]*Normal[1]*dSigmayy_phi2 + Velocity_i[2]*Normal[2]*dSigmazz_phi2
                                + (Velocity_i[0]*Normal[1] + Velocity_i[1]*Normal[0])*dSigmaxy_phi2
                                + (Velocity_i[0]*Normal[2] + Velocity_i[2]*Normal[0])*dSigmaxz_phi2
                                + (Velocity_i[2]*Normal[1] + Velocity_i[1]*Normal[2])*dSigmayz_phi2 );
      val_Jacobian_ii[0][3] = -( Velocity_i[0]*Normal[0]*dSigmaxx_phi3 + Velocity_i[1]*Normal[1]*dSigmayy_phi3 + Velocity_i[2]*Normal[2]*dSigmazz_phi3
                                + (Velocity_i[0]*Normal[1] + Velocity_i[1]*Normal[0])*dSigmaxy_phi3
                                + (Velocity_i[0]*Normal[2] + Velocity_i[2]*Normal[0])*dSigmaxz_phi3
                                + (Velocity_i[2]*Normal[1] + Velocity_i[1]*Normal[2])*dSigmayz_phi3 );
      val_Jacobian_ii[0][4] = (sq_vel_i - Pressure_i/(Density_i*Gamma_Minus_One)) * dSigma5_psi5;
      
      val_Jacobian_ii[1][0] = 0;
      val_Jacobian_ii[1][1] = Normal[0]*dSigmaxx_phi1 + Normal[1]*dSigmaxy_phi1 + Normal[2]*dSigmaxz_phi1;
      val_Jacobian_ii[1][2] = Normal[0]*dSigmaxx_phi2 + Normal[1]*dSigmaxy_phi2 + Normal[2]*dSigmaxz_phi2;
      val_Jacobian_ii[1][3] = Normal[0]*dSigmaxx_phi3 + Normal[1]*dSigmaxy_phi3 + Normal[2]*dSigmaxz_phi3;
      val_Jacobian_ii[1][4] = -Velocity_i[0]*dSigma5_psi5;
      
      val_Jacobian_ii[2][0] = 0;
      val_Jacobian_ii[2][1] = Normal[0]*dSigmaxy_phi1 + Normal[1]*dSigmayy_phi1 + Normal[2]*dSigmayz_phi1;
      val_Jacobian_ii[2][2] = Normal[0]*dSigmaxy_phi2 + Normal[1]*dSigmayy_phi2 + Normal[2]*dSigmayz_phi2;
      val_Jacobian_ii[2][3] = Normal[0]*dSigmaxy_phi3 + Normal[1]*dSigmayy_phi3 + Normal[2]*dSigmayz_phi3;
      val_Jacobian_ii[2][4] = -Velocity_i[1]*dSigma5_psi5;
      
      val_Jacobian_ii[3][0] = 0;
      val_Jacobian_ii[3][1] = Normal[0]*dSigmaxz_phi1 + Normal[1]*dSigmayz_phi1 + Normal[2]*dSigmazz_phi1;
      val_Jacobian_ii[3][2] = Normal[0]*dSigmaxz_phi2 + Normal[1]*dSigmayz_phi2 + Normal[2]*dSigmazz_phi2;
      val_Jacobian_ii[3][3] = Normal[0]*dSigmaxz_phi3 + Normal[1]*dSigmayz_phi3 + Normal[2]*dSigmazz_phi3;
      val_Jacobian_ii[3][4] = -Velocity_i[2]*dSigma5_psi5;
      
      val_Jacobian_ii[4][0] = 0;
      val_Jacobian_ii[4][1] = 0;
      val_Jacobian_ii[4][2] = 0;
      val_Jacobian_ii[4][3] = 0;
      val_Jacobian_ii[4][4] = dSigma5_psi5;
      
      for (iVar = 0; iVar < nVar; iVar++)
        for (jVar = 0; jVar < nVar; jVar++)
          val_Jacobian_ij[iVar][jVar] = -val_Jacobian_ii[iVar][jVar];
    }
    
    /*--- Residual at jPoint ---*/
    
    Sigma_xx = ViscDens_j * (FOUR3 * Mean_GradPhi[0][0] -  TWO3 * Mean_GradPhi[1][1] - TWO3  * Mean_GradPhi[2][2]);
    Sigma_yy = ViscDens_j * (-TWO3 * Mean_GradPhi[0][0] + FOUR3 * Mean_GradPhi[1][1] - TWO3  * Mean_GradPhi[2][2]);
    Sigma_zz = ViscDens_j * (-TWO3 * Mean_GradPhi[0][0] -  TWO3 * Mean_GradPhi[1][1] + FOUR3 * Mean_GradPhi[2][2]);
    Sigma_xy = ViscDens_j * (Mean_GradPhi[1][0] + Mean_GradPhi[0][1]);
    Sigma_xz = ViscDens_j * (Mean_GradPhi[2][0] + Mean_GradPhi[0][2]);
    Sigma_yz = ViscDens_j * (Mean_GradPhi[2][1] + Mean_GradPhi[1][2]);
    Sigma_xx5 = ViscDens_j * ( FOUR3 * Velocity_j[0] * Mean_GradPsiE[0] -  TWO3 * Velocity_j[1] * Mean_GradPsiE[1] -  TWO3 * Velocity_j[2] * Mean_GradPsiE[2]);
    Sigma_yy5 = ViscDens_j * (- TWO3 * Velocity_j[0] * Mean_GradPsiE[0] + FOUR3 * Velocity_j[1] * Mean_GradPsiE[1] -  TWO3 * Velocity_j[2] * Mean_GradPsiE[2]);
    Sigma_zz5 = ViscDens_j * (- TWO3 * Velocity_j[0] * Mean_GradPsiE[0] -  TWO3 * Velocity_j[1] * Mean_GradPsiE[1] + FOUR3 * Velocity_j[2] * Mean_GradPsiE[2]);
    Sigma_xy5 = ViscDens_j * (Velocity_j[0] * Mean_GradPsiE[1] + Velocity_j[1] * Mean_GradPsiE[0]);
    Sigma_xz5 = ViscDens_j * (Velocity_j[0] * Mean_GradPsiE[2] + Velocity_j[2] * Mean_GradPsiE[0]);
    Sigma_yz5 = ViscDens_j * (Velocity_j[1] * Mean_GradPsiE[2] + Velocity_j[2] * Mean_GradPsiE[1]);
    Sigma_5   = XiDens_j * dPhiE_dn;
    eta_xx = Sigma_xx + Sigma_xx5; eta_yy = Sigma_yy + Sigma_yy5; eta_zz = Sigma_zz + Sigma_zz5;
    eta_xy = Sigma_xy + Sigma_xy5; eta_xz = Sigma_xz + Sigma_xz5; eta_yz = Sigma_yz + Sigma_yz5;
    
    val_residual_j[0] = - (Velocity_j[0] * Normal[0] * eta_xx  + Velocity_j[1] * Normal[1] * eta_yy + Velocity_j[2] * Normal[2] * eta_zz
                           + (Velocity_j[0] * Normal[1] + Velocity_j[1] * Normal[0]) * eta_xy
                           + (Velocity_j[0] * Normal[2] + Velocity_j[2] * Normal[0]) * eta_xz
                           + (Velocity_j[2] * Normal[1] + Velocity_j[1] * Normal[2]) * eta_yz
                           - (sq_vel_j - Pressure_j/(Density_j*Gamma_Minus_One)) * Sigma_5);
    val_residual_j[1] = (eta_xx * Normal[0] + eta_xy * Normal[1] + eta_xz * Normal[2] - Velocity_j[0] * Sigma_5);
    val_residual_j[2] = (eta_xy * Normal[0] + eta_yy * Normal[1] + eta_yz * Normal[2] - Velocity_j[1] * Sigma_5);
    val_residual_j[3] = (eta_xz * Normal[0] + eta_yz * Normal[1] + eta_zz * Normal[2] - Velocity_j[2] * Sigma_5);
    val_residual_j[4] = (Sigma_5);
    
    /*--- Computation of the Jacobians at Point j---*/
    
    if (implicit) {
      
      dSigmaxx_phi1 = FOUR3 * ViscDens_j * Edge_Vector[0]/dist_ij_2;
      dSigmaxx_phi2 = -TWO3 * ViscDens_j * Edge_Vector[1]/dist_ij_2;
      dSigmaxx_phi3 = -TWO3 * ViscDens_j * Edge_Vector[2]/dist_ij_2;
      dSigmayy_phi1 = -TWO3 * ViscDens_j * Edge_Vector[0]/dist_ij_2;
      dSigmayy_phi2 = FOUR3 * ViscDens_j * Edge_Vector[1]/dist_ij_2;
      dSigmayy_phi3 = -TWO3 * ViscDens_j * Edge_Vector[2]/dist_ij_2;
      dSigmazz_phi1 = -TWO3 * ViscDens_j * Edge_Vector[0]/dist_ij_2;
      dSigmazz_phi2 = -TWO3 * ViscDens_j * Edge_Vector[1]/dist_ij_2;
      dSigmazz_phi3 = FOUR3 * ViscDens_j * Edge_Vector[2]/dist_ij_2;
      dSigmaxy_phi1 = ViscDens_j * Edge_Vector[1]/dist_ij_2;
      dSigmaxy_phi2 = ViscDens_j * Edge_Vector[0]/dist_ij_2;
      dSigmaxy_phi3 = 0;
      dSigmaxz_phi1 = ViscDens_j * Edge_Vector[2]/dist_ij_2;
      dSigmaxz_phi2 = 0;
      dSigmaxz_phi3 = ViscDens_j * Edge_Vector[0]/dist_ij_2;
      dSigmayz_phi1 = 0;
      dSigmayz_phi2 = ViscDens_j * Edge_Vector[2]/dist_ij_2;
      dSigmayz_phi3 = ViscDens_j * Edge_Vector[1]/dist_ij_2;
      
      //      dSigmaxx5_psi5 = ViscDens_j * ( FOUR3*Velocity_j[0]*Edge_Vector[0] -  TWO3*Velocity_j[1]*Edge_Vector[1] -  TWO3*Velocity_j[2]*Edge_Vector[2])/dist_ij_2;
      //      dSigmayy5_psi5 = ViscDens_j * (- TWO3*Velocity_j[0]*Edge_Vector[0] + FOUR3*Velocity_j[1]*Edge_Vector[1] -  TWO3*Velocity_j[2]*Edge_Vector[2])/dist_ij_2;
      //      dSigmazz5_psi5 = ViscDens_j * (- TWO3*Velocity_j[0]*Edge_Vector[0] -  TWO3*Velocity_j[1]*Edge_Vector[1] + FOUR3*Velocity_j[2]*Edge_Vector[2])/dist_ij_2;
      //      dSigmaxy5_psi5 = ViscDens_j * ( Velocity_j[0]*Edge_Vector[1] + Velocity_j[1]*Edge_Vector[0] )/dist_ij_2;
      //      dSigmaxz5_psi5 = ViscDens_j * ( Velocity_j[0]*Edge_Vector[2] + Velocity_j[2]*Edge_Vector[0] )/dist_ij_2;
      //      dSigmayz5_psi5 = ViscDens_j * ( Velocity_j[1]*Edge_Vector[2] + Velocity_j[2]*Edge_Vector[1] )/dist_ij_2;
      dSigma5_psi5   = XiDens_j * ( Edge_Vector[0]*Normal[0] + Edge_Vector[1]*Normal[1] + Edge_Vector[2]*Normal[2] )/dist_ij_2;
      
      val_Jacobian_jj[0][0] = 0;
      val_Jacobian_jj[0][1] = -( Velocity_j[0]*Normal[0]*dSigmaxx_phi1 + Velocity_j[1]*Normal[1]*dSigmayy_phi1 + Velocity_j[2]*Normal[2]*dSigmazz_phi1
                                + (Velocity_j[0]*Normal[1] + Velocity_j[1]*Normal[0])*dSigmaxy_phi1
                                + (Velocity_j[0]*Normal[2] + Velocity_j[2]*Normal[0])*dSigmaxz_phi1
                                + (Velocity_j[2]*Normal[1] + Velocity_j[1]*Normal[2])*dSigmayz_phi1 );
      val_Jacobian_jj[0][2] = -( Velocity_j[0]*Normal[0]*dSigmaxx_phi2 + Velocity_j[1]*Normal[1]*dSigmayy_phi2 + Velocity_j[2]*Normal[2]*dSigmazz_phi2
                                + (Velocity_j[0]*Normal[1] + Velocity_j[1]*Normal[0])*dSigmaxy_phi2
                                + (Velocity_j[0]*Normal[2] + Velocity_j[2]*Normal[0])*dSigmaxz_phi2
                                + (Velocity_j[2]*Normal[1] + Velocity_j[1]*Normal[2])*dSigmayz_phi2 );
      val_Jacobian_jj[0][3] = -( Velocity_j[0]*Normal[0]*dSigmaxx_phi3 + Velocity_j[1]*Normal[1]*dSigmayy_phi3 + Velocity_j[2]*Normal[2]*dSigmazz_phi3
                                + (Velocity_j[0]*Normal[1] + Velocity_j[1]*Normal[0])*dSigmaxy_phi3
                                + (Velocity_j[0]*Normal[2] + Velocity_j[2]*Normal[0])*dSigmaxz_phi3
                                + (Velocity_j[2]*Normal[1] + Velocity_j[1]*Normal[2])*dSigmayz_phi3 );
      val_Jacobian_jj[0][4] = (sq_vel_j - Pressure_j/(Density_j*Gamma_Minus_One)) * dSigma5_psi5;
      
      val_Jacobian_jj[1][0] = 0;
      val_Jacobian_jj[1][1] = Normal[0]*dSigmaxx_phi1 + Normal[1]*dSigmaxy_phi1 + Normal[2]*dSigmaxz_phi1;
      val_Jacobian_jj[1][2] = Normal[0]*dSigmaxx_phi2 + Normal[1]*dSigmaxy_phi2 + Normal[2]*dSigmaxz_phi2;
      val_Jacobian_jj[1][3] = Normal[0]*dSigmaxx_phi3 + Normal[1]*dSigmaxy_phi3 + Normal[2]*dSigmaxz_phi3;
      val_Jacobian_jj[1][4] = -Velocity_j[0]*dSigma5_psi5;
      
      val_Jacobian_jj[2][0] = 0;
      val_Jacobian_jj[2][1] = Normal[0]*dSigmaxy_phi1 + Normal[1]*dSigmayy_phi1 + Normal[2]*dSigmayz_phi1;
      val_Jacobian_jj[2][2] = Normal[0]*dSigmaxy_phi2 + Normal[1]*dSigmayy_phi2 + Normal[2]*dSigmayz_phi2;
      val_Jacobian_jj[2][3] = Normal[0]*dSigmaxy_phi3 + Normal[1]*dSigmayy_phi3 + Normal[2]*dSigmayz_phi3;
      val_Jacobian_jj[2][4] = -Velocity_j[1]*dSigma5_psi5;
      
      val_Jacobian_jj[3][0] = 0;
      val_Jacobian_jj[3][1] = Normal[0]*dSigmaxz_phi1 + Normal[1]*dSigmayz_phi1 + Normal[2]*dSigmazz_phi1;
      val_Jacobian_jj[3][2] = Normal[0]*dSigmaxz_phi2 + Normal[1]*dSigmayz_phi2 + Normal[2]*dSigmazz_phi2;
      val_Jacobian_jj[3][3] = Normal[0]*dSigmaxz_phi3 + Normal[1]*dSigmayz_phi3 + Normal[2]*dSigmazz_phi3;
      val_Jacobian_jj[3][4] = -Velocity_j[2]*dSigma5_psi5;
      
      val_Jacobian_jj[4][0] = 0;
      val_Jacobian_jj[4][1] = 0;
      val_Jacobian_jj[4][2] = 0;
      val_Jacobian_jj[4][3] = 0;
      val_Jacobian_jj[4][4] = dSigma5_psi5;
      
      for (iVar = 0; iVar < nVar; iVar++)
        for (jVar = 0; jVar < nVar; jVar++)
          val_Jacobian_ji[iVar][jVar] = -val_Jacobian_jj[iVar][jVar];
    }
    
  }
  else if (nDim == 2) {
    
    /*--- Residual at iPoint ---*/
    
    Sigma_xx = ViscDens_i * (FOUR3 * Mean_GradPhi[0][0] -  TWO3 * Mean_GradPhi[1][1]);
    Sigma_yy = ViscDens_i * (-TWO3 * Mean_GradPhi[0][0] + FOUR3 * Mean_GradPhi[1][1]);
    Sigma_xy = ViscDens_i * (Mean_GradPhi[1][0] + Mean_GradPhi[0][1]);
    Sigma_xx5 = ViscDens_i * ( FOUR3 * Velocity_i[0] * Mean_GradPsiE[0] -  TWO3 * Velocity_i[1] * Mean_GradPsiE[1]);
    Sigma_yy5 = ViscDens_i * (- TWO3 * Velocity_i[0] * Mean_GradPsiE[0] + FOUR3 * Velocity_i[1] * Mean_GradPsiE[1]);
    Sigma_xy5 = ViscDens_i * (Velocity_i[0] * Mean_GradPsiE[1] + Velocity_i[1] * Mean_GradPsiE[0]);
    Sigma_5   = XiDens_i * dPhiE_dn;
    eta_xx = Sigma_xx + Sigma_xx5; eta_yy = Sigma_yy + Sigma_yy5; eta_xy = Sigma_xy + Sigma_xy5;
    
    val_residual_i[0] = - (Velocity_i[0] * Normal[0] * eta_xx  + Velocity_i[1] * Normal[1] * eta_yy
                           + (Velocity_i[0] * Normal[1] + Velocity_i[1] * Normal[0]) * eta_xy
                           - (sq_vel_i - Pressure_i/(Density_i*Gamma_Minus_One)) * Sigma_5);
    val_residual_i[1] = (eta_xx * Normal[0] + eta_xy * Normal[1] - Velocity_i[0] * Sigma_5);
    val_residual_i[2] = (eta_xy * Normal[0] + eta_yy * Normal[1] - Velocity_i[1] * Sigma_5);
    val_residual_i[3] = (Sigma_5);
    
    /*--- Computation of the Jacobians at Point i---*/
    
    if (implicit) {
      
      dSigmaxx_phi1 = -FOUR3 * ViscDens_i * Edge_Vector[0]/dist_ij_2;
      dSigmaxx_phi2 =   TWO3 * ViscDens_i * Edge_Vector[1]/dist_ij_2;
      dSigmayy_phi1 =   TWO3 * ViscDens_i * Edge_Vector[0]/dist_ij_2;
      dSigmayy_phi2 = -FOUR3 * ViscDens_i * Edge_Vector[1]/dist_ij_2;
      dSigmaxy_phi1 = -ViscDens_i * Edge_Vector[1]/dist_ij_2;
      dSigmaxy_phi2 = -ViscDens_i * Edge_Vector[0]/dist_ij_2;
      
      //      dSigmaxx5_psi5 = -ViscDens_i * ( FOUR3*Velocity_i[0]*Edge_Vector[0] -  TWO3*Velocity_i[1]*Edge_Vector[1] )/dist_ij_2;
      //      dSigmayy5_psi5 = -ViscDens_i * (- TWO3*Velocity_i[0]*Edge_Vector[0] + FOUR3*Velocity_i[1]*Edge_Vector[1] )/dist_ij_2;
      //      dSigmaxy5_psi5 = -ViscDens_i * ( Velocity_i[0]*Edge_Vector[1] + Velocity_i[1]*Edge_Vector[0] )/dist_ij_2;
      dSigma5_psi5   = -XiDens_i * ( Edge_Vector[0]*Normal[0] + Edge_Vector[1]*Normal[1] )/dist_ij_2;
      
      val_Jacobian_ii[0][0] = 0;
      
      val_Jacobian_ii[0][1] = -( Velocity_i[0]*Normal[0]*dSigmaxx_phi1 + Velocity_i[1]*Normal[1]*dSigmayy_phi1
                                + (Velocity_i[0]*Normal[1] + Velocity_i[1]*Normal[0])*dSigmaxy_phi1 );
      val_Jacobian_ii[0][2] = -( Velocity_i[0]*Normal[0]*dSigmaxx_phi2 + Velocity_i[1]*Normal[1]*dSigmayy_phi2
                                + (Velocity_i[0]*Normal[1] + Velocity_i[1]*Normal[0])*dSigmaxy_phi2 );
      val_Jacobian_ii[0][3] = (sq_vel_i - Pressure_i/(Density_i*Gamma_Minus_One)) * dSigma5_psi5;
      
      val_Jacobian_ii[1][0] = 0;
      val_Jacobian_ii[1][1] = Normal[0]*dSigmaxx_phi1 + Normal[1]*dSigmaxy_phi1;
      val_Jacobian_ii[1][2] = Normal[0]*dSigmaxx_phi2 + Normal[1]*dSigmaxy_phi2;
      val_Jacobian_ii[1][3] = -Velocity_i[0]*dSigma5_psi5;
      
      val_Jacobian_ii[2][0] = 0;
      val_Jacobian_ii[2][1] = Normal[0]*dSigmaxy_phi1 + Normal[1]*dSigmayy_phi1;
      val_Jacobian_ii[2][2] = Normal[0]*dSigmaxy_phi2 + Normal[1]*dSigmayy_phi2;
      val_Jacobian_ii[2][3] = -Velocity_i[1]*dSigma5_psi5;
      
      val_Jacobian_ii[3][0] = 0;
      val_Jacobian_ii[3][1] = 0;
      val_Jacobian_ii[3][2] = 0;
      val_Jacobian_ii[3][3] = dSigma5_psi5;
      
      for (iVar = 0; iVar < nVar; iVar++)
        for (jVar = 0; jVar < nVar; jVar++)
          val_Jacobian_ij[iVar][jVar] = -val_Jacobian_ii[iVar][jVar];
    }
    
    /*--- Residual at jPoint ---*/
    Sigma_xx = ViscDens_j * (FOUR3 * Mean_GradPhi[0][0] -  TWO3 * Mean_GradPhi[1][1]);
    Sigma_yy = ViscDens_j * (-TWO3 * Mean_GradPhi[0][0] + FOUR3 * Mean_GradPhi[1][1]);
    Sigma_xy = ViscDens_j * (Mean_GradPhi[1][0] + Mean_GradPhi[0][1]);
    Sigma_xx5 = ViscDens_j * ( FOUR3 * Velocity_j[0] * Mean_GradPsiE[0] -  TWO3 * Velocity_j[1] * Mean_GradPsiE[1]);
    Sigma_yy5 = ViscDens_j * (- TWO3 * Velocity_j[0] * Mean_GradPsiE[0] + FOUR3 * Velocity_j[1] * Mean_GradPsiE[1]);
    Sigma_xy5 = ViscDens_j * (Velocity_j[0] * Mean_GradPsiE[1] + Velocity_j[1] * Mean_GradPsiE[0]);
    Sigma_5   = XiDens_j * dPhiE_dn;
    eta_xx = Sigma_xx + Sigma_xx5; eta_yy = Sigma_yy + Sigma_yy5; eta_xy = Sigma_xy + Sigma_xy5;
    
    val_residual_j[0] = - (Velocity_j[0] * Normal[0] * eta_xx  + Velocity_j[1] * Normal[1] * eta_yy
                           + (Velocity_j[0] * Normal[1] + Velocity_j[1] * Normal[0]) * eta_xy
                           - (sq_vel_j - Pressure_j/(Density_j*Gamma_Minus_One)) * Sigma_5);
    val_residual_j[1] = (eta_xx * Normal[0] + eta_xy * Normal[1]  - Velocity_j[0] * Sigma_5);
    val_residual_j[2] = (eta_xy * Normal[0] + eta_yy * Normal[1]  - Velocity_j[1] * Sigma_5);
    val_residual_j[3] = (Sigma_5);
    
    /*--- Computation of the Jacobians at Point j---*/
    if (implicit) {
      dSigmaxx_phi1 = FOUR3 * ViscDens_j * Edge_Vector[0]/dist_ij_2;
      dSigmaxx_phi2 = -TWO3 * ViscDens_j * Edge_Vector[1]/dist_ij_2;
      dSigmayy_phi1 = -TWO3 * ViscDens_j * Edge_Vector[0]/dist_ij_2;
      dSigmayy_phi2 = FOUR3 * ViscDens_j * Edge_Vector[1]/dist_ij_2;
      dSigmaxy_phi1 = ViscDens_j * Edge_Vector[1]/dist_ij_2;
      dSigmaxy_phi2 = ViscDens_j * Edge_Vector[0]/dist_ij_2;
      
      //      dSigmaxx5_psi5 = ViscDens_j * ( FOUR3*Velocity_j[0]*Edge_Vector[0] -  TWO3*Velocity_j[1]*Edge_Vector[1] )/dist_ij_2;
      //      dSigmayy5_psi5 = ViscDens_j * (- TWO3*Velocity_j[0]*Edge_Vector[0] + FOUR3*Velocity_j[1]*Edge_Vector[1] )/dist_ij_2;
      //      dSigmaxy5_psi5 = ViscDens_j * ( Velocity_j[0]*Edge_Vector[1] + Velocity_j[1]*Edge_Vector[0] )/dist_ij_2;
      dSigma5_psi5   = XiDens_j * ( Edge_Vector[0]*Normal[0] + Edge_Vector[1]*Normal[1] )/dist_ij_2;
      
      val_Jacobian_jj[0][0] = 0;
      val_Jacobian_jj[0][1] = -( Velocity_j[0]*Normal[0]*dSigmaxx_phi1 + Velocity_j[1]*Normal[1]*dSigmayy_phi1
                                + (Velocity_j[0]*Normal[1] + Velocity_j[1]*Normal[0])*dSigmaxy_phi1 );
      val_Jacobian_jj[0][2] = -( Velocity_j[0]*Normal[0]*dSigmaxx_phi2 + Velocity_j[1]*Normal[1]*dSigmayy_phi2
                                + (Velocity_j[0]*Normal[1] + Velocity_j[1]*Normal[0])*dSigmaxy_phi2 );
      val_Jacobian_jj[0][3] = (sq_vel_j - Pressure_j/(Density_j*Gamma_Minus_One)) * dSigma5_psi5;
      
      val_Jacobian_jj[1][0] = 0;
      val_Jacobian_jj[1][1] = Normal[0]*dSigmaxx_phi1 + Normal[1]*dSigmaxy_phi1;
      val_Jacobian_jj[1][2] = Normal[0]*dSigmaxx_phi2 + Normal[1]*dSigmaxy_phi2;
      val_Jacobian_jj[1][3] = -Velocity_j[0]*dSigma5_psi5;
      
      val_Jacobian_jj[2][0] = 0;
      val_Jacobian_jj[2][1] = Normal[0]*dSigmaxy_phi1 + Normal[1]*dSigmayy_phi1;
      val_Jacobian_jj[2][2] = Normal[0]*dSigmaxy_phi2 + Normal[1]*dSigmayy_phi2;
      val_Jacobian_jj[2][3] = -Velocity_j[1]*dSigma5_psi5;
      
      val_Jacobian_jj[3][0] = 0;
      val_Jacobian_jj[3][1] = 0;
      val_Jacobian_jj[3][2] = 0;
      val_Jacobian_jj[3][3] = dSigma5_psi5;
      
      for (iVar = 0; iVar < nVar; iVar++)
        for (jVar = 0; jVar < nVar; jVar++)
          val_Jacobian_ji[iVar][jVar] = -val_Jacobian_jj[iVar][jVar];
    }
  }
 
}

void CNumerics::GetPrimitive2Conservative (su2double *val_Mean_PrimVar, su2double *val_Mean_SecVar, su2double **val_Jac_PC) {

  unsigned short iVar, jVar, iDim;

  // order of primitives: T, vx, vy, vz, P, rho, h, c, MuLam, MuEddy, kt, Cp
  // order of secondary: dPdrho_e, dPde_rho, dTdrho_e, dTde_rho, dmudrho_T, dmudT_rho, dktdrho_T, dktdT_rho

  su2double vx = val_Mean_PrimVar[1];
  su2double vy = val_Mean_PrimVar[2];
  su2double vz = val_Mean_PrimVar[3];
  su2double rho = val_Mean_PrimVar[nDim+2];
  su2double P = val_Mean_PrimVar[nDim+1];
  su2double e = val_Mean_PrimVar[nDim+3] - P/rho;
  su2double dTdrho_e = val_Mean_SecVar[2];
  su2double dTde_rho = val_Mean_SecVar[3];

  su2double sqvel = 0.0;

  for (iDim = 0; iDim < nDim; iDim++) {
    sqvel += val_Mean_PrimVar[iDim+1]*val_Mean_PrimVar[iDim+1];
  }

  /*--- Initialize the Jacobian matrix ---*/
  for (iVar = 0; iVar < nVar; iVar++) {
    for (jVar = 0; jVar < nVar; jVar++) {
      val_Jac_PC[iVar][jVar] = 0.0;
    }
  }

  /*--- Primitives to conservatives Jacobian matrix : (T, vx, vy, vz, rho) --> (u1, u2, u3, u4, u5) ---*/
  if (nDim == 2) {

  val_Jac_PC[0][0] = dTdrho_e - e/rho*dTde_rho + 0.5*dTde_rho*sqvel/rho;
  val_Jac_PC[0][1] = -1/rho*dTde_rho*vx;
  val_Jac_PC[0][2] = -1/rho*dTde_rho*vy;
  val_Jac_PC[0][3] = 1/rho*dTde_rho;

  val_Jac_PC[1][0] = -vx/rho;
  val_Jac_PC[1][1] = 1/rho;
  val_Jac_PC[1][2] = 0.0;
  val_Jac_PC[1][3] = 0.0;

  val_Jac_PC[2][0] = -vy/rho;
  val_Jac_PC[2][1] = 0.0;
  val_Jac_PC[2][2] = 1/rho;
  val_Jac_PC[2][3] = 0.0;

  val_Jac_PC[3][0] = 1.0;
  val_Jac_PC[3][1] = 0.0;
  val_Jac_PC[3][2] = 0.0;
  val_Jac_PC[3][3] = 0.0;

  }
  else {

  val_Jac_PC[0][0] = dTdrho_e - e/rho*dTde_rho + 0.5*dTde_rho*sqvel/rho;
  val_Jac_PC[0][1] = -1/rho*dTde_rho*vx;
  val_Jac_PC[0][2] = -1/rho*dTde_rho*vy;
  val_Jac_PC[0][3] = -1/rho*dTde_rho*vz;
  val_Jac_PC[0][4] = 1/rho*dTde_rho;

  val_Jac_PC[1][0] = -vx/rho;
  val_Jac_PC[1][1] = 1/rho;
  val_Jac_PC[1][2] = 0.0;
  val_Jac_PC[1][3] = 0.0;
  val_Jac_PC[1][4] = 0.0;

  val_Jac_PC[2][0] = -vy/rho;
  val_Jac_PC[2][1] = 0.0;
  val_Jac_PC[2][2] = 1/rho;
  val_Jac_PC[2][3] = 0.0;
  val_Jac_PC[2][4] = 0.0;

  val_Jac_PC[3][0] = -vz/rho;
  val_Jac_PC[3][1] = 0.0;
  val_Jac_PC[3][2] = 0.0;
  val_Jac_PC[3][3] = 1/rho;
  val_Jac_PC[3][4] = 0.0;

  val_Jac_PC[4][0] = 1.0;
  val_Jac_PC[4][1] = 0.0;
  val_Jac_PC[4][2] = 0.0;
  val_Jac_PC[4][3] = 0.0;
  val_Jac_PC[4][4] = 0.0;

  }
}

void CNumerics::CreateBasis(su2double *val_Normal) {
  unsigned short iDim;
  su2double modm, modl;
  
  /*--- Define l as a vector in the plane normal to the supplied vector ---*/
  l[0] = 0.0;
  l[1] = -val_Normal[2];
  l[2] = val_Normal[1];
  
  /*--- Check for the zero vector and re-assign if needed ---*/
  if (l[0] == 0.0 && l[1] == 0.0 && l[2] == 0.0) {
    l[0] = -val_Normal[2];
    l[1] = 0.0;
    l[2] = val_Normal[0];
  }
  
  /*--- Take vector product of n * l to make m ---*/
  m[0] = val_Normal[1]*l[2] - val_Normal[2]*l[1];
  m[1] = val_Normal[2]*l[0] - val_Normal[0]*l[2];
  m[2] = val_Normal[0]*l[1] - val_Normal[1]*l[0];
  
  /*--- Normalize ---*/
  modm =0 ; modl = 0;
  for (iDim =0 ; iDim < nDim; iDim++) {
    modm += m[iDim]*m[iDim];
    modl += l[iDim]*l[iDim];
  }
  modm = sqrt(modm);
  modl = sqrt(modl);
  for (iDim =0 ; iDim < nDim; iDim++) {
    l[iDim] = l[iDim]/modl;
    m[iDim] = m[iDim]/modm;
  }
}

void CNumerics::SetRoe_Dissipation(const su2double Dissipation_i,
                                   const su2double Dissipation_j,
                                   const su2double Sensor_i,
                                   const su2double Sensor_j,
                                   su2double& Dissipation_ij,
                                   CConfig *config) {

  /*--- Check for valid input ---*/

  assert((Dissipation_i >= 0) && (Dissipation_i <= 1));
  assert((Dissipation_j >= 0) && (Dissipation_j <= 1));
  assert((Sensor_i >= 0) && (Sensor_i <= 1));
  assert((Sensor_j >= 0) && (Sensor_j <= 1));

  unsigned short roe_low_diss = config->GetKind_RoeLowDiss();

  /*--- A minimum level of upwinding is used to enhance stability ---*/

  const su2double Min_Dissipation = 0.05;
  
  const su2double Mean_Dissipation = 0.5*(Dissipation_i + Dissipation_j);
  const su2double Mean_Sensor = 0.5*(Sensor_i + Sensor_j);
  
  if (roe_low_diss == FD || roe_low_diss == FD_DUCROS){

    Dissipation_ij = max(0.05,1.0 - (0.5 * (Dissipation_i + Dissipation_j)));
    
    if (roe_low_diss == FD_DUCROS){
      
      /*--- See Jonhsen et al. JCP 229 (2010) pag. 1234 ---*/

      su2double Ducros_ij;
      
      if (0.5*(Sensor_i + Sensor_j) > 0.65)
        Ducros_ij = 1.0;
      else
        Ducros_ij = 0.05;
      
      Dissipation_ij = max(Ducros_ij, Dissipation_ij);
    }

  } else if (roe_low_diss == NTS) {
    
    Dissipation_ij = max(Min_Dissipation, Mean_Dissipation);

  } else if (roe_low_diss == NTS_DUCROS) {

    /*--- See Xiao et al. INT J HEAT FLUID FL 51 (2015) pag. 141
     * https://doi.org/10.1016/j.ijheatfluidflow.2014.10.007 ---*/

    const su2double phi1 = Mean_Sensor;
    const su2double phi2 = Mean_Dissipation;

    Dissipation_ij = max(Min_Dissipation, phi1 + phi2 - (phi1*phi2));

  } else {

    SU2_MPI::Error("Unrecognized upwind/central blending scheme!",
                   CURRENT_FUNCTION);

  }

}

void CNumerics::EigenDecomposition(su2double **A_ij, su2double **Eig_Vec, su2double *Eig_Val, unsigned short n){
  int iDim,jDim;
  su2double *e = new su2double [n];
  for (iDim= 0; iDim< n; iDim++){
    e[iDim] = 0;
    for (jDim = 0; jDim < n; jDim++){
      Eig_Vec[iDim][jDim] = A_ij[iDim][jDim];
    }
  }
  tred2(Eig_Vec, Eig_Val, e, n);
  tql2(Eig_Vec, Eig_Val, e, n);

  delete [] e;
}

void CNumerics::EigenRecomposition(su2double **A_ij, su2double **Eig_Vec, su2double *Eig_Val, unsigned short n){
  unsigned short i,j,k;
  su2double **tmp = new su2double* [n];
  su2double **deltaN = new su2double* [n];

  for (i= 0; i< n; i++){
    tmp[i] = new su2double [n];
    deltaN[i] = new su2double [n];
  }

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      if (i == j) deltaN[i][j] = 1.0;
      else deltaN[i][j]=0.0;
    }
  }

  for (i= 0; i< n; i++){
    for (j = 0; j < n; j++){
      tmp[i][j] = 0.0;
      for (k = 0; k < n; k++){
        tmp[i][j] += Eig_Vec[i][k] * Eig_Val[k] * deltaN[k][j];
      }
    }
  }

  for (i= 0; i< n; i++){
    for (j = 0; j < n; j++){
      A_ij[i][j] = 0.0;
      for (k = 0; k < n; k++){
        A_ij[i][j] += tmp[i][k] * Eig_Vec[j][k];
      }
    }
  }

  for (i = 0; i < n; i++){
    delete [] tmp[i];
    delete [] deltaN[i];
  }
  delete [] tmp;
  delete [] deltaN;
}

void CNumerics::tred2(su2double **V, su2double *d, su2double *e, unsigned short n) {

/* Author:

 * Original FORTRAN77 version by Smith, Boyle, Dongarra, Garbow, Ikebe,
 * Klema, Moler.
 * C++ version by Aashwin Mishra and Jayant Mukhopadhaya.

 * Reference:

 * Martin, Reinsch, Wilkinson,
 * TRED2,
 * Numerische Mathematik,
 * Volume 11, pages 181-195, 1968.

 * James Wilkinson, Christian Reinsch,
 * Handbook for Automatic Computation,
 * Volume II, Linear Algebra, Part 2,
 * Springer, 1971,
 * ISBN: 0387054146,
 * LC: QA251.W67.

 * Brian Smith, James Boyle, Jack Dongarra, Burton Garbow,
 * Yasuhiko Ikebe, Virginia Klema, Cleve Moler,
 * Matrix Eigensystem Routines, EISPACK Guide,
 * Lecture Notes in Computer Science, Volume 6,
 * Springer Verlag, 1976,
 * ISBN13: 978-3540075462,
 * LC: QA193.M37

*/

  unsigned short i,j,k;

  for (j = 0; j < n; j++) {
    d[j] = V[n-1][j];
  }

  /* Householder reduction to tridiagonal form. */

  for (i = n-1; i > 0; i--) {

    /* Scale to avoid under/overflow. */

    su2double scale = 0.0;
    su2double h = 0.0;
    for (k = 0; k < i; k++) {
      scale = scale + fabs(d[k]);
    }
    if (scale == 0.0) {
      e[i] = d[i-1];
      for (j = 0; j < i; j++) {
        d[j] = V[i-1][j];
        V[i][j] = 0.0;
        V[j][i] = 0.0;
      }
    }
    else {

      /* Generate Householder vector. */

      for (k = 0; k < i; k++) {
        d[k] /= scale;
        h += d[k] * d[k];
      }
      su2double f = d[i-1];
      su2double g = sqrt(h);
      if (f > 0) {
        g = -g;
      }
      e[i] = scale * g;
      h = h - f * g;
      d[i-1] = f - g;
      for (j = 0; j < i; j++) {
        e[j] = 0.0;
      }

      /* Apply similarity transformation to remaining columns. */

      for (j = 0; j < i; j++) {
        f = d[j];
        V[j][i] = f;
        g = e[j] + V[j][j] * f;
        for (k = j+1; k <= i-1; k++) {
          g += V[k][j] * d[k];
          e[k] += V[k][j] * f;
        }
        e[j] = g;
      }
      f = 0.0;
      for (j = 0; j < i; j++) {
        e[j] /= h;
        f += e[j] * d[j];
      }
      su2double hh = f / (h + h);
      for (j = 0; j < i; j++) {
        e[j] -= hh * d[j];
      }
      for (j = 0; j < i; j++) {
        f = d[j];
        g = e[j];
        for (k = j; k <= i-1; k++) {
            V[k][j] -= (f * e[k] + g * d[k]);
        }
        d[j] = V[i-1][j];
        V[i][j] = 0.0;
      }
    }
    d[i] = h;
  }

  /* Accumulate transformations. */

  for (i = 0; i < n-1; i++) {
    V[n-1][i] = V[i][i];
    V[i][i] = 1.0;
    su2double h = d[i+1];
    if (h != 0.0) {
      for (k = 0; k <= i; k++) {
        d[k] = V[k][i+1] / h;
      }
      for (j = 0; j <= i; j++) {
        su2double g = 0.0;
        for (k = 0; k <= i; k++) {
          g += V[k][i+1] * V[k][j];
        }
        for (k = 0; k <= i; k++) {
          V[k][j] -= g * d[k];
        }
      }
    }
    for (k = 0; k <= i; k++) {
      V[k][i+1] = 0.0;
    }
  }
  for (j = 0; j < n; j++) {
    d[j] = V[n-1][j];
    V[n-1][j] = 0.0;
  }
  V[n-1][n-1] = 1.0;
  e[0] = 0.0;
}

void CNumerics::tql2(su2double **V, su2double *d, su2double *e, unsigned short n) {

/* Author:

 * Original FORTRAN77 version by Smith, Boyle, Dongarra, Garbow, Ikebe,
 * Klema, Moler.
 * C++ version by Aashwin Mishra and Jayant Mukhopadhaya.

 * Reference:

 * Bowdler, Martin, Reinsch, Wilkinson,
 * TQL2,
 * Numerische Mathematik,
 * Volume 11, pages 293-306, 1968.

 * James Wilkinson, Christian Reinsch,
 * Handbook for Automatic Computation,
 * Volume II, Linear Algebra, Part 2,
 * Springer, 1971,
 * ISBN: 0387054146,
 * LC: QA251.W67.

 * Brian Smith, James Boyle, Jack Dongarra, Burton Garbow,
 * Yasuhiko Ikebe, Virginia Klema, Cleve Moler,
 * Matrix Eigensystem Routines, EISPACK Guide,
 * Lecture Notes in Computer Science, Volume 6,
 * Springer Verlag, 1976,
 * ISBN13: 978-3540075462,
 * LC: QA193.M37

*/
  
  int i,j,k,l;
  for (i = 1; i < n; i++) {
    e[i-1] = e[i];
  }
  e[n-1] = 0.0;

  su2double f = 0.0;
  su2double tst1 = 0.0;
  su2double eps = pow(2.0,-52.0);
  for (l = 0; l < n; l++) {

    /* Find small subdiagonal element */

    tst1 = max(tst1,(fabs(d[l]) + fabs(e[l])));
    int m = l;
    while (m < n) {
      if (fabs(e[m]) <= eps*tst1) {
        break;
      }
      m++;
    }

    /* If m == l, d[l] is an eigenvalue, */
    /* otherwise, iterate.               */

    if (m > l) {
      int iter = 0;
      do {
        iter = iter + 1;  /* (Could check iteration count here.) */

        /* Compute implicit shift */

        su2double g = d[l];
        su2double p = (d[l+1] - g) / (2.0 * e[l]);
        su2double r = sqrt(p*p+1.0);
        if (p < 0) {
          r = -r;
        }
        d[l] = e[l] / (p + r);
        d[l+1] = e[l] * (p + r);
        su2double dl1 = d[l+1];
        su2double h = g - d[l];
        for (i = l+2; i < n; i++) {
          d[i] -= h;
        }
        f = f + h;

        /* Implicit QL transformation. */

        p = d[m];
        su2double c = 1.0;
        su2double c2 = c;
        su2double c3 = c;
        su2double el1 = e[l+1];
        su2double s = 0.0;
        su2double s2 = 0.0;
        for (i = m-1; i >= l; i--) {
          c3 = c2;
          c2 = c;
          s2 = s;
          g = c * e[i];
          h = c * p;
          r = sqrt(p*p+e[i]*e[i]);
          e[i+1] = s * r;
          s = e[i] / r;
          c = p / r;
          p = c * d[i] - s * g;
          d[i+1] = h + s * (c * g + s * d[i]);

          /* Accumulate transformation. */

          for (k = 0; k < n; k++) {
            h = V[k][i+1];
            V[k][i+1] = s * V[k][i] + c * h;
            V[k][i] = c * V[k][i] - s * h;
          }
        }
        p = -s * s2 * c3 * el1 * e[l] / dl1;
        e[l] = s * p;
        d[l] = c * p;

        /* Check for convergence. */

      } while (fabs(e[l]) > eps*tst1);
    }
    d[l] = d[l] + f;
    e[l] = 0.0;
  }

  /* Sort eigenvalues and corresponding vectors. */

  for (i = 0; i < n-1; i++) {
    k = i;
    su2double p = d[i];
    for (j = i+1; j < n; j++) {
      if (d[j] < p) {
        k = j;
        p = d[j];
      }
    }
    if (k != i) {
      d[k] = d[i];
      d[i] = p;
      for (j = 0; j < n; j++) {
          p = V[j][i];
          V[j][i] = V[j][k];
          V[j][k] = p;
      }
    }
  }
}

CSourceNothing::CSourceNothing(unsigned short val_nDim, unsigned short val_nVar, CConfig *config) : CNumerics(val_nDim, val_nVar, config) { }

CSourceNothing::~CSourceNothing(void) { }
