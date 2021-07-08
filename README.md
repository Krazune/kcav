# KCAV
Krazune's Cellular Automata Viewer is a viewer for a collection of popular, and custom, 2d cellular automata that uses images as input.

## Version
Current version: **2021.07.1**

The version format is "*\<year\>.\<zero padded month\>.\<revision number\>*".

## Cellular Automata Included
| Name | Identifier | Rules | Neighborhood type | Input image conversion | Notes |
|---|---|---|---|---|---|
| Game of Life | life | [Rules available at wikipedia.](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) | Moore neighborhood | Black, and white, pixels are kept as is. Each pixel is converted into the closest valid color. | The most popular cellular automaton. |
| Seeds | seeds | [Rules available at wikipedia.](https://en.wikipedia.org/wiki/Seeds_(cellular_automaton) | Moore neighborhood | Black, and white, pixels are kept as is. Each pixel is converted into the closest valid color. | |
| Brian's Brain | brians-brain | [Rules available at wikipedia.](https://en.wikipedia.org/wiki/Brian%27s_Brain) | Moore neighborhood | Black, white, and 100% blue, pixels are kept as is. Each pixel is converted into the closest valid color. | |
| Live Free or Die | lfod | [Rules available at LifeWiki.](https://conwaylife.com/wiki/OCA:Live_Free_or_Die) | Moore neighborhood | Black, and white, pixels are kept as is.  | Each pixel is converted into the closest valid color. |
| Kladiators | kladiators | Each pixel turns into the color of the neighbor pixel with the highest sum of r, g, and b channels. If multiple pixels have the same sum, priorities follow anti-clockwise direction. | Von Neumann neighborhood | The image is used as is, no conversion is needed. | Created by Krazune. It's not a very interesting ruleset. |
| Pilots | pilots | The following rules are normalized into cellular automata mechanics. Red pixels move right, blue pixels move down, green pixels move left, and yellow pixels move up. When multiple colors hit the same cell, that cell turns black, and stays black forever. All other cells are white. | 4 immediate neighbors | Input pixels are converted to their closest valid color. | Created by Krazune. |

*\* This formula is not very accurate, but it's good enough for this.*
In the future, more rulesets should be added to the collection.

## Usage
```./kcav --help```

```./kcav --version```

```./kcav <ruleset identifier> <image path> [options]```

### Options

```--time <time, in milseconds, per generation frame>```

## Dependencies
This project uses [Boost](https://www.boost.org/) 1.75, [SFML](https://www.sfml-dev.org/index.php) 2.5.1, and [Google Test](https://github.com/google/googletest) 1.10.x, earlier versions might be compatible.

## License
[MIT License](LICENSE.md)

## Notes
The performance of this program is not good.
This generator was created for educational purposes only.