//Determination of minimum Cell length in simulation domain is calculated according
//to interThermalPhaseChangeFoam developed by Rattner and MahdiNabil

PtrList<volScalarField> minCellLengthFluid(fluidRegions.size());

forAll(fluidRegions, regionI)
{
	minCellLengthFluid.set
	(
		regionI,
		new volScalarField
        (
            IOobject
            (
                "minCellLengthFluid",
                    runTime.timeName(),
                    fluidRegions[regionI],
                    IOobject::NO_READ,
                    IOobject::NO_WRITE
                ),
				fluidRegions[regionI],
				dimensionedScalar("dummy", dimensionSet(0,1,0,0,0,0,0), 0)
            )
        );

	const cellList& cells = fluidRegions[regionI].cells();		
	forAll(cells, cellI)
	{
		scalar minLength = GREAT;
		const labelList& cellEdges = fluidRegions[regionI].cellEdges()[cellI];
		
	   forAll (cellEdges, edgeI)
		{
			scalar length = fluidRegions[regionI].edges()[ cellEdges[edgeI] ].mag( fluidRegions[regionI].points() );
			if (length < minLength)
			{  
				minLength = length;
			}
		}	
		minCellLengthFluid[regionI] = minLength * dimensionedScalar("l", dimensionSet(0,1,0,0,0,0,0), 1);
	}

	Info<< "Minimum cell length: " <<  gMin(minCellLengthFluid[regionI]) << endl;
}	