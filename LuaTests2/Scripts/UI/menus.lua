Menu1={
	MenuComponent={
		ID=10,
		Name="Main Menu",
		Optionvec={"New Game","Test - Pause Menu","Exit Game"},
		Xvec={10,10,10},
		Yvec={50,55,60},
		IDvec={1,11,0},
		Timeout_enable=0,
		Timeout=0,
		Active=1,
		MiscPhrase="Whatever endures can be created only gradually by long-continued work and careful reflection.",
	}
}

Menu2={
	MenuComponent={
		ID=11,
		Name="Game Menu",
		Optionvec={"Save game","Load game","Options","End game","Return to game"},
		Xvec={10,10,10,10,10},
		Yvec={50,55,60,65,70},
		IDvec={-1,-1,-1,10,-2},
		Timeout_enable=0,
		Timeout=0,
		Active=0,

	}
}

Menu3={
	MenuComponent={
		ID=99,
		Name="Game Over",
		Optionvec={"Restart Game","Return to Main Menu"},
		Xvec={10,10},
		Yvec={50,55},
		IDvec={12,10},
		Timeout_enable=1,
		Timeout=60,
		Active=0,
	}
}

UI1={
	UIComponent={
		Name="FPS Counter",
		ID=200,
		ID_exactMatch=0,
		ID_minRange=100,
		ID_maxRange=900,
		Display="FPS:",
		Xposition=5,
		Yposition=5,
		PercentPositioning=1,
	}
}

UI2={
	UIComponent={
		Name="Game Title",
		ID=201,
		ID_exactMatch=0,
		ID_minRange=100,
		ID_maxRange=199,
		Display="Amplified Illusions",
		Xposition=35,
		Yposition=10,
		PercentPositioning=1,
	}
}

Background={
	UIComponent={
		Name="Background Image",
		ID=202,
		ID_exactMatch=0,
		ID_minRange=100,
		ID_maxRange=900,
		Display="by SCP:Entertainment",
		Xposition=80,
		Yposition=90,
		PercentPositioning=1,
	},

	GraphicsComponent={
	filename="Assets/Textures/splashintro.jpg",
		position_x=840,
		position_y=525,
		size_x=960,
		size_y=540,
	}
}















