/*//////////////////////////////////////////////////////////////////////////////
// CMT Cosmic Muon Tomography project //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

  Copyright (c) 2014, Universita' degli Studi di Padova, INFN sez. di Padova
  All rights reserved

  Authors: Andrea Rigoni Garola < andrea.rigoni@pd.infn.it >

  ------------------------------------------------------------------
  This library is free software;  you  can  redistribute  it  and/or
  modify it  under the  terms  of  the  GNU  Lesser  General  Public
  License as published  by  the  Free  Software  Foundation;  either
  version 3.0 of the License, or (at your option) any later version.

  This library is  distributed in  the hope that it will  be useful,
  but  WITHOUT ANY WARRANTY;  without  even  the implied warranty of
  MERCHANTABILITY  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of  the GNU Lesser General  Public
  License along with this library.

//////////////////////////////////////////////////////////////////////////////*/

#include <iostream>

//#include "boost/preprocessor.hpp"
//#include "boost/preprocessor/repetition.hpp"

#include "Core/MplSequenceCombiner.h"

#include "Core/ClassCompound.h"

#include "Core/ClassFactory.h"
#include "Core/Serializable.h"

#include "testing-prototype.h"

using namespace uLib;



////////////////////////////////////////////////////////////////////////////////
// WORKING EXAMPLE //

namespace Test {



class Voxel {
public:
    virtual void Set(float) = 0;
    virtual float Get() const = 0;
    virtual ~Voxel() {}
};

class VoxelMean : public Voxel {
public:
    VoxelMean() : m_data(0), m_count(0) {}
    void  Set(float data) { m_data += data; ++m_count; }
    float Get() const { return m_data / m_count; }
private:
    float m_data;
    int m_count;
};

class VoxelVal : public Voxel {
public:
    VoxelVal() : m_data(0) {}
    void Set(float data) { m_data = data; }
    float Get() const { return m_data; }
private:
    float m_data;
};




class VoxCount {
public:
    template < class T >
    int Count(const Vector<T> &ref ) const {
        return ref.size();
    }
};

class VoxCountOver {
public:
    VoxCountOver() : m_threshold(0) {}

    template < class T >
    int Count(const Vector<T> &ref ) const {
        int count = 0 ;
        foreach (const T &el, ref) {
            if( el.Get() >= m_threshold ) ++count;
        }
        return count;
    }
    float m_threshold;
};




class VoxelVectorBase {
public:
    virtual float Get(int) const = 0;
    virtual void Set(int,float) = 0;
    virtual int Size() const = 0;
    virtual int Count() const = 0;
    virtual ~VoxelVectorBase() {}
};

template < class T >
void copy(T *src, T *dst) { }

void copy(VoxelVectorBase *src, VoxelVectorBase *dst) {
    for(int i=0; i<src->Size(); ++i) {
        dst->Set(i,src->Get(i));
    }
}


template < class VoxType,
           class CounterType >
class VoxelVector : public VoxelVectorBase {
public:

    VoxelVector() {} // remove?
    VoxelVector( const VoxType *A1, const CounterType *A2 ) {
        (void) A1;
        SetA2(A2);
    }

    void * GetA2() { return &m_counter; }
    void   SetA2(const void *A2) { m_counter = *A2; }

    float Get(int id) const { return m_data[id].Get(); }
    void Set(int id, float data) {
        if(id >= Size()) m_data.resize(id+1);
        m_data[id].Set(data);
    }
    int Size() const { return m_data.size(); }
    int Count() const { return m_counter.Count(m_data); }
private:
    friend class VoxelVectorFactory;
    CounterType     m_counter;
    Vector<VoxType> m_data;
};


class VoxelVectorFactory {
public:
    VoxelVectorFactory() :
        m_id1(0), m_id2(0)
    {
        m_base = m_factory.Create(0,0);
    }

    ~VoxelVectorFactory() {
        delete m_base;
    }

    VoxelVectorBase * operator -> () const { return m_base; }

    template < typename T >
    void SetVoxel() {
        int id = m_factory.FindS1<T>();
        VoxelVectorBase * newbase = m_factory.Create(id,m_id2);
        Test::copy(m_base,newbase); // *newbase = *m_base;

        //

        delete m_base;
        m_base = newbase;
    }

    template < typename T >
    void SetCounter(const T &ref) {
        int id = m_factory.FindS2<T>();
        VoxelVectorBase * newbase = m_factory.Create(m_id1,id);
        Test::copy(m_base,newbase); // *newbase = *m_base;

        //

        delete m_base;
        m_base = newbase;
    }


private:
    RegisteredClassFactory2< VoxelVectorBase, VoxelVector, mpl::vector<VoxelMean,VoxelVal>, mpl::vector<VoxCount,VoxCountOver> > m_factory;
    int m_id1, m_id2;
    VoxelVectorBase * m_base;
};
} // Test







struct B1 {
    B1() : m_b1(1) {}
    int m_b1;
};

struct B2 {
    B2() : m_b2(2) {}
    int m_b2;
};

struct B3 {
    B3() : m_b3(3) {}
    int m_b3;
};

struct B3b {
    B3b() : m_b3(3) {}
    int m_b3; // learn to handle ambiguity ..
};


int main() {

    ClassCompound< B1, B2 > h1;
    ClassCompound< B2, B3, B1 > h2;


    h1.A0::m_b1 = 111;
    h1.A1::m_b2 = 222;

    h2 = h1;

    std::cout << "h1: " << h1.A0::m_b1 << " " << h1.A1::m_b2 << "\n";
    std::cout << "h2: " << h2.A0::m_b2 << " " << h2.A1::m_b3 << "\n";

}













