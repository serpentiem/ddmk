let dmc3_typeSizes =
[
	[ "InputData"              , 12   ],
	[ "MotionData"             , 2    ],
	[ "ActorEventData"         , 8    ],
	[ "ModelMetadata"          , 80   ],
	[ "ModelData"              , 1920 ],
	[ "DevilModelMetadataDante", 33   ],
	[ "ShadowData"             , 192  ],
	[ "PhysicsData"            , 240  ],
	[ "PhysicsMetadata"        , 320  ],
	[ "PhysicsLinkData"        , 192  ],
	[ "PhysicsLinkMetadata"    , 264  ],
	[ "BodyPartData"           , 288  ],
	[ "RecoveryData"           , 112  ],
	[ "WeaponData"             , 296  ],
	[ "PlayerData"             , 18   ],
	[ "CameraData"             , 512  ],
	[ "CollisionData"          , 656  ],
	[ "StyleData"              , 352  ],
	[ "EnemyVectorDataMetadata", 16   ],
	[ "ItemData"               , 4    ],
	[ "ModelPartitionData"     , 896  ],
	[ "LockOnData"             , 8568 ],
];

typeSizes_Reset();
typeSizes_Add(dmc3_typeSizes);
