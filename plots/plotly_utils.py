'''
Utilities and definitions to be used when plotting the spacepoints
with Plotly
'''

# Create custom colors to be used in plots
custom_colors = {'dark_green': 0x1C8356, 'purple': 0x636EFA, 'teal': 0x19D3F3,
                 'light_purple': 0xAB63FA, 'pink': 0xFF6692, 'brown': 0x8C564B}

# Dictionary mapping PDG number to name
pdg2string = {-11: 'Positron', 11: 'Electron', -13: 'Anti-muon', 13: 'Muon', 22: 'Gamma', 1000180400: 'Ar40',
              111: 'Pi0', -211: 'Pi-', 211: 'Pi+', 321: 'K+', 2112: "Neutron", 2212: 'Proton'}

# Dictionary mapping PDG number to color
colors = {-11: 'red', 11: 'green', -13: 'blue', 13: 'magenta', 22: 'goldenrod', 1000180400: 'black',
          111: custom_colors["dark_green"], -211: custom_colors["purple"], 211: custom_colors["teal"],
          321: custom_colors["light_purple"], 2112: custom_colors["pink"], 2212: custom_colors["brown"], 0: 'black'}

'''
 Plotly marker settings
'''
# Reco beam particles
reco_beam_marker = {'size': 4, 'color': '',  'symbol': 'diamond', 'colorscale': "Viridis", 'opacity': 0.8,
               'cmax': 1., 'cmin': 0.}

# Reco daughter particles
reco_daughter_marker = {'size': 4, 'color': '',  'symbol': 'diamond', 'colorscale': "Viridis", 'opacity': 0.8,
                   'cmax': 1., 'cmin': 0.}

# MC truth beam particles
truth_beam_marker = {'size': 4, 'color': '', 'symbol': 'cross', 'colorscale': "Viridis", 'opacity': 0.8,
               'cmax': 1., 'cmin': 0., 'line': {'color': 'black', 'width': 3}}

# MC truth daughter particles
truth_daughter_marker = {'size': 4, 'color': '', 'colorscale': "Viridis", 'opacity': 0.8,
               'cmax': 1., 'cmin': 0., 'line': {'color': 'black', 'width': 3}}