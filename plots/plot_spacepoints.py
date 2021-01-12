import uproot
import numpy as np
import plotly.graph_objs as go
from plotly.offline import plot
import sys

#################################
#
# Script to plot spacepoints for a given event.
# Simply specify the file, run and event numbers and
# the spacepoints will be plotted. Choose whether to
# to plot beam and daughter tracks, showers or both.
#
#################################

dark_green = 0x1C8356
purple = 0x636EFA
teal = 0x19D3F3
light_purple = 0xAB63FA
pink = 0xFF6692
brown = 0x8C564B
pdg2string = {-11: 'Positron', 11: 'Electron', -13: 'Anti-muon', 13: 'Muon', 22: 'Gamma',
              111: 'Pi0', -211: 'Pi-', 211: 'Pi+', 321: 'K+', 2112: "Neutron", 2212: 'Proton'}


def open_file(file_name):
    try:
        file1 = uproot.open(file_name)
        tree = file1["pduneana/beamana"]
    except FileNotFoundError:
        print("Could not find file", file_name)
        return
    return tree


def find_event_idx(tree, run, evt):
    runs = tree["run"].array(library="np")
    events = tree["event"].array(library="np")
    run_event = np.vstack((runs, events)).T

    event_idx = np.where((run_event[:, 0] == run) & (run_event[:, 1] == evt))[0]

    if len(event_idx) > 1:
        print("Found too many matches! Matches =", len(event_idx))
    elif len(event_idx) > 0:
        print("Found run/event match at index", event_idx[0])
    else:
        event_idx = -1
        print("No matches!")

    return event_idx


def plot(tree, event_idx, run, evt, plot_opt):

    colors = {-11: 'red', 11: 'green', -13: 'blue', 13: 'magenta', 22: 'goldenrod',
              111: dark_green, -211: purple, 211: teal, 321: light_purple, 2112: pink, 2212: brown}

    beam_marker = {'size': 2, 'color': 'red', 'colorscale': "Viridis", 'opacity': 0.8, 'cmax': 1., 'cmin': 0.}
    daughter_marker = {'size': 2, 'color': 'orange', 'colorscale': "Viridis", 'opacity': 0.8, 'cmax': 1., 'cmin': 0.}
    shower_marker = {'size': 2, 'color': 'green', 'colorscale': "Viridis", 'opacity': 0.8, 'cmax': 1., 'cmin': 0.}

    reco_beam_x = tree["reco_beam_spacePts_X"].array(library="np")[event_idx][0]
    reco_beam_y = tree["reco_beam_spacePts_Y"].array(library="np")[event_idx][0]
    reco_beam_z = tree["reco_beam_spacePts_Z"].array(library="np")[event_idx][0]

    reco_daughter_x = tree["reco_daughter_spacePts_X"].array(library="np")[event_idx][0]
    reco_daughter_y = tree["reco_daughter_spacePts_X"].array(library="np")[event_idx][0]
    reco_daughter_z = tree["reco_daughter_spacePts_X"].array(library="np")[event_idx][0]

    reco_daughter_shower_x = tree["reco_daughter_spacePts_X"].array(library="np")[event_idx][0]
    reco_daughter_shower_y = tree["reco_daughter_spacePts_X"].array(library="np")[event_idx][0]
    reco_daughter_shower_z = tree["reco_daughter_spacePts_X"].array(library="np")[event_idx][0]

    reco_beam_pdg = tree["true_beam_PDG"].array(library="np")[event_idx][0]
    daughter_pdg = tree["true_beam_daughter_PDG"].array(library="np")[event_idx][0]

    if len(reco_beam_x) < 1:
        print("Empty event, skipping plots!")
        return

    fig = go.Figure()

    # Plot the beam particle
    print(reco_beam_pdg)
    beam_marker['color'] = colors[reco_beam_pdg]
    fig.add_trace(go.Scatter3d(x=reco_beam_x,
                               y=reco_beam_y,
                               z=reco_beam_z,
                               name=pdg2string[reco_beam_pdg],
                               mode='markers',
                               marker=beam_marker
                               )
                  )

    # Plot the reco daughter tracks
    if plot_opt['daughter_track']:
        for x, y, z, pdg in zip(reco_daughter_x, reco_daughter_y, reco_daughter_z, daughter_pdg):
            daughter_marker['color'] = colors[pdg]
            fig.add_trace(go.Scatter3d(x=x,
                                       y=y,
                                       z=z,
                                       name=pdg2string[pdg],
                                       mode='markers',
                                       marker=daughter_marker
                                       )
                          )

    # Plot the reco daughter showers
    if plot_opt['daughter_shower']:
        for x, y, z, pdg in zip(reco_daughter_shower_x, reco_daughter_shower_y, reco_daughter_shower_z, daughter_pdg):
            shower_marker['color'] = colors[pdg]
            fig.add_trace(go.Scatter3d(x=x,
                                       y=y,
                                       z=z,
                                       name=pdg2string[pdg],
                                       mode='markers',
                                       marker=shower_marker
                                       )
                          )

    title = "Run " + str(run) + " event " + str(evt)
    fig.update_layout(title=title, showlegend=True, legend={'itemsizing': 'constant'})
    fig.show()


def plot_event(file, run, evt, plot_opt):
    tree = open_file(file)
    if tree is None:
        return

    idx = find_event_idx(tree, run, evt)
    if idx == -1:
        return

    plot(tree, idx, run, evt, plot_opt)


########################################

file = "../../pduneana.root"
run = 13778829
event = 1068
plot_opts = {'daughter_track': True, 'daughter_shower': True}

plot_event(file, run, event, plot_opts)
