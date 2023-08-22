#include "Math/Vector.isph"

struct FStaticAcceleratedManagedSignificanceInfo
{
    // Basic info
    FVector3f Location;
    float SignificanceDistanceSquare;
    int8 NumTickStages;
    float TickRateResponseExp;

    // Updated data.
	int8 CurrentTickStage;	
	float CurrentSignificance;
    
    int8 bIsSignificant;
    int8 bWasSignificant;
    int8 bDidChangeTickState;

    // non ispc data
    bool bSupportsTickRateDilation;
};

inline float square(const float& a)
{
    return a * a;
}

export void ComputeSignififance( const uniform FVector3f ViewPoints[],
                                 const uniform int32 NumViewports,
                                 uniform FStaticAcceleratedManagedSignificanceInfo uniform Data[],
                                 const uniform int32 Begin,
                                 const uniform int32 End)
{
    const varying FVector3f v1 = ViewPoints[0];

    foreach(i = Begin ... End)
    {    
        FStaticAcceleratedManagedSignificanceInfo* Entry = &Data[i];
        const FVector3f v2 = Entry->Location;
                
        float A = square(v2.V[0] - v1.V[0]);
        float B = square(v2.V[1] - v1.V[1]);
        float C = square(v2.V[2] - v1.V[2]);
            
        const float DistSquared = A+B+C;

        // > 0 is relevant
        const float NewSignifiance = min(1.f - max((DistSquared / Entry->SignificanceDistanceSquare), 0.0f),1.0);
        const float OldSignifiance = Entry->CurrentSignificance;

        // Update values
        Entry->CurrentSignificance = NewSignifiance; 
            
        Entry->bIsSignificant = NewSignifiance >= 0.01f;
        Entry->bWasSignificant = OldSignifiance == -1.f ? -1 : OldSignifiance >= 0.01f;

        // Set tick interval.
        const int8 NewCurrentTickStage = Entry->NumTickStages * NewSignifiance;

        Entry->bDidChangeTickState = Entry->CurrentTickStage != NewCurrentTickStage;
        Entry->CurrentTickStage = NewCurrentTickStage;
    }
};