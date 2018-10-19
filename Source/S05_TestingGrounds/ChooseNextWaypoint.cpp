// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrollingGaurd.h" // TODO remove  couplign
#include "AIController.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	// TODO protect against empty waypoints. 

	// Get the patrol points
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	auto PatrollingGaurd = Cast<APatrollingGaurd>(ControlledPawn);
	auto PatrolPoints = PatrollingGaurd->PatrolPointsCPP;

	// Set next waypoint
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();

	// Fix for crash
	if (PatrolPoints.Num() > 0) {
		auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
		BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

		// Cycle the index
		auto NextIndex = (Index + 1) % PatrolPoints.Num();
		BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);
	}

	//UE_LOG(LogTemp, Warning, TEXT("Waypoint Index: %i"), Index);
	return EBTNodeResult::Succeeded;
}
