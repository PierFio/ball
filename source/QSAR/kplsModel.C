/* kplsModel.C
 * 
 * Copyright (C) 2009 Marcel Schumann
 * 
 * This file is part of QuEasy -- A Toolbox for Automated QSAR Model
 * Construction and Validation.
 * QuEasy is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 * 
 * QuEasy is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

// -*- Mode: weights_++; tab-width: 2; -*-
// vi: set ts=2:
//
//

#include <BALL/QSAR/kplsModel.h>
#include <BALL/QSAR/mlrModel.h>
#include <BALL/MATHS/LINALG/matrixInverter.h>

namespace BALL
{
	namespace QSAR
			{


		KPLSModel::KPLSModel(const QSARData& q, int k_type, double p1, double p2) : KernelModel(q,k_type,p1,p2) 
		{
			no_components_=1;
			type_="KPLS";
		}


		KPLSModel::KPLSModel(const QSARData& q, Vector<double>& w) : KernelModel(q,w) 
		{
			no_components_=1;
			type_="KPLS";
		}


		KPLSModel::KPLSModel(const QSARData& q, String s1, String s2) : KernelModel(q,s1,s2) 
		{
			no_components_=1;
			type_="KPLS";
		}


		KPLSModel::KPLSModel(const QSARData& q, const LinearModel& lm, int column) : KernelModel(q,lm,column)
		{
			no_components_=1;
			type_="KPLS";
		}


		KPLSModel::~KPLSModel()
		{
		}

		int KPLSModel::getNoComponents()
		{
			return no_components_;
		}

		void KPLSModel::setNoComponents(int d)
		{
			no_components_=d;
		}


		void KPLSModel::setParameters(vector<double>& v)
		{
			if(v.size()!=1)
			{
				String c = "Wrong number of model parameters! Needed: 1;";
				c = c+" given: "+String(v.size());
				throw Exception::ModelParameterError(__FILE__,__LINE__,c.c_str());
			}
			no_components_ = (int) v[0];
		}


		vector<double> KPLSModel::getParameters() const
		{
			vector<double> d;
			d.push_back(no_components_);
			return d;
		}


		void KPLSModel::train()
		{	
			if(descriptor_matrix_.Ncols()==0)
			{
				throw Exception::InconsistentUsage(__FILE__,__LINE__,"Data must be read into the model before training!");
			}
		// 	if(descriptor_matrix_.Ncols()<no_components_)
		// 	{
		// 		throw Exception::TooManyPLSComponents(__FILE__,__LINE__,no_components_,descriptor_matrix_.Ncols());
		// 	}
			
			kernel->calculateKernelMatrix(descriptor_matrix_, K_);

			Matrix<double> P;  // Matrix P saves all vectors p

			int cols=K_.Ncols();
			
			// determine the number of components that are to be created.
			// no_components_ contains the number of components desired by the user, 
			// but obviously we cannot calculate more PLS components than features
			int features = descriptor_matrix_.Ncols();
			uint components_to_create = no_components_;
			if(features<no_components_) components_to_create=features;

			U_.resize(K_.Nrows(),components_to_create);
			loadings_.resize(cols,components_to_create);
			weights_.resize(Y_.getColumnCount(),components_to_create);
			latent_variables_.resize(K_.Nrows(),components_to_create);
			P.resize(cols,components_to_create);
			
			Vector<double> w; w.setVectorType(1);
			Vector<double> t; t.setVectorType(1);
			Vector<double> c; c.setVectorType(1);
			Vector<double> u(K_.Nrows()); c.setVectorType(1);
			for (uint i=1; i<=u.getSize(); i++)
			{
				u(i)=Y_(i,1);	
			}
			Vector<double> u_old; u_old.setVectorType(1);
			
			for(uint j=0; j<components_to_create; j++)
			{
				for(int i=0;i<10000 ;i++)
				{	
					w = K_.t()*u / Statistics::scalarProduct(u);
					w = w / Statistics::euclNorm(w);
					t = K_*w;
					c = Y_.t()*t / Statistics::scalarProduct(t);
					u_old=u;
					u = Y_*c / Statistics::scalarProduct(c); 
				
					if (Statistics::euclDistance(u,u_old)/Statistics::euclNorm(u)>0.0000001) 
					{ 
						continue;				
					}
					else  // if u has converged
					{
						break;
					}
				}
				Vector<double> p = K_.t()*t / Statistics::scalarProduct(t);
				
				Matrix<double> TP; 
				t.dotProduct(p,TP); // t.p.t() -> dim. nxn
				K_ -= TP;
				//Y_ = Y_ - t*c.t();
				
				U_.copyVectorToColumn(u,j+1);
				loadings_.copyVectorToColumn(w,j+1);
				weights_.copyVectorToColumn(c,j+1);
				P.copyVectorToColumn(p,j+1);
				latent_variables_.copyVectorToColumn(t,j+1);
			}

		// 	try // p's are not orthogonal to each other, so that in rare cases P.t()*loadings_ is not invertible
		// 	{
		// 		loadings_ = loadings_*(P.t()*loadings_).i();
		// 	}
		// 	catch(BALL::Exception::MatrixIsSingular e)
		// 	{
		// 		Matrix<double> I; I.setToIdentity(P.Ncols());
		// 		I*=0.001;
		// 		loadings_ = loadings_*(P.t()*loadings_+I).i();
		// 	}

			Matrix<double> m = P.t()*loadings_;
			MatrixInverter<double, StandardTraits> inverter(m);
			inverter.computePseudoInverse();

			loadings_ = loadings_*inverter.getPseudoInverse();
			
			training_result_=loadings_*weights_.t();
			
			calculateOffsets();
		}


		bool KPLSModel::optimizeParameters(int k, int no_steps)
		{
			double best_q2=0;
			int best_no=1;
			for(int i=1; i<=no_steps && i<=(int)data->getNoDescriptors() && (descriptor_IDs_.empty() || i<(int)descriptor_IDs_.size());i++)
			{	
				no_components_=i;
				validation->crossValidation(k);
				if(validation->getQ2()>best_q2)
				{
					best_q2=validation->getQ2();
					best_no=i;
				}
				else if(validation->getQ2()<0.75*best_q2)
				{
					break;
				}
			}
			no_components_=best_no;
			validation->setQ2(best_q2);
			
			return 1;
		}

		const BALL::Matrix<double>* KPLSModel::getU()
		{ 
			return &U_;
		}
	}
}