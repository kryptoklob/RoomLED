// Definiitions for all of the possible modes for the LEDs
// Each mode has an associated ID that corresponds to the ID of the mode in the Arduino codebase
// Each mode has a certain number of presets aka "versions"

var modes = [
  { name: "AllOff", baseID: 0, versions: 1 },
  { name: "AllOn", baseID: 1, versions: 1 },
  { name: "One-Sin", baseID: 16, versions: 6 },
  { name: "Two-Sin", baseID: 3, versions: 10 },
  { name: "Three-Sin", baseID: 28, versions: 3 },
  { name: "Confetti", baseID: 39, versions: 1 },
  { name: "Sinelon", baseID: 40, versions: 1 },
  { name: "Juggle", baseID: 41, versions: 1 },
  { name: "Noise", baseID: 37, versions: 2 },
  { name: "Rainbow", baseID: 31, versions: 6 },
  { name: "Matrix", baseID: 13, versions: 3 },
  { name: "Twinkle", baseID: 2, versions: 1 },
  { name: "Pop-Fade", baseID: 22, versions: 6 },
  { name: "Dot-Beat", baseID: 42, versions: 1 },
  { name: "Lightnings", baseID: 43, versions: 1 }
]

//module.exports.modes = modes;
