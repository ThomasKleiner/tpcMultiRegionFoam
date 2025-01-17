/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2013 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::phaseChangeTwoPhaseMixtureCond

Description

SourceFiles
    phaseChangeTwoPhaseMixtureCond.C
    newPhaseChangeModel.C

\*---------------------------------------------------------------------------*/

#ifndef phaseChangeTwoPhaseMixtureCond_H
#define phaseChangeTwoPhaseMixtureCond_H

#include "immiscibleIncompressibleTwoPhaseMixtureCond.H"
#include "typeInfo.H"
#include "runTimeSelectionTables.H"
#include "volFields.H"
#include "dimensionedScalar.H"
#include "autoPtr.H"
#include "Pair.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                Class phaseChangeTwoPhaseMixtureCond Declaration
\*---------------------------------------------------------------------------*/

class phaseChangeTwoPhaseMixtureCond
:
    public immiscibleIncompressibleTwoPhaseMixtureCond
{

protected:

    // Protected data

        dictionary phaseChangeTwoPhaseMixtureCondCoeffs_;

        //- Saturation vapour pressure
//        dimensionedScalar pSat_;


    // Private Member Functions

        //- Disallow copy construct
        phaseChangeTwoPhaseMixtureCond(const phaseChangeTwoPhaseMixtureCond&);

        //- Disallow default bitwise assignment
        void operator=(const phaseChangeTwoPhaseMixtureCond&);


public:

    //- Runtime type information
    TypeName("phaseChangeTwoPhaseMixtureCond");


    // Declare run-time constructor selection table

        declareRunTimeSelectionTable
        (
            autoPtr,
            phaseChangeTwoPhaseMixtureCond,
            components,
            (
                const volVectorField& U,
                const surfaceScalarField& phi
            ),
            (U, phi)
        );


    // Selectors

        //- Return a reference to the selected phaseChange model
        static autoPtr<phaseChangeTwoPhaseMixtureCond> New
        (
            const volVectorField& U,
            const surfaceScalarField& phi
        );


    // Constructors

        //- Construct from components
        phaseChangeTwoPhaseMixtureCond
        (
            const word& type,
            const volVectorField& U,
            const surfaceScalarField& phi
        );


    //- Destructor
    virtual ~phaseChangeTwoPhaseMixtureCond()
    {}


    // Member Functions

        //- return the mass transfer rate for face fraction adjustment in Cell due to phase change
        virtual Pair<tmp<volScalarField> > mDotAlphal() const = 0;

        //- return the mass transfer rate for pressure adjustment in Cell due to phase change
        virtual Pair<tmp<volScalarField> > mDotP() const = 0;

        //- return the mass transfer rate for face fraction adjustment in Cell due to phase change
        Pair<tmp<volScalarField> > vDotAlphal() const;

        //- return the mass transfer rate for pressure adjustment in Cell due to phase change
        Pair<tmp<volScalarField> > vDotP() const;

        //- Correct the phaseChange model
        virtual void correct() = 0;

        //- Read the transportProperties dictionary and update
        virtual bool read() = 0;

    //- Selector
    static autoPtr<phaseChangeTwoPhaseMixtureCond> New
    (
        const fvMesh&,
        const word& phaseName=word::null
    );
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
