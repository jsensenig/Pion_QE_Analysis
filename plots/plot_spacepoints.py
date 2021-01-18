import uproot
import numpy as np
import plotly.graph_objs as go
import plotly_utils as util
import sys


'''

 Script to plot spacepoints for a given event.
 Simply specify the file, run and event numbers and
 the spacepoints will be plotted. Choose whether to
 to plot beam and daughter tracks, showers or both.
 
 Run:
      python plot_spacepoints.py <ROOT_file> <run> <event>
'''


def open_file(file_name, tree_dir):
    try:
        file1 = uproot.open(file_name)
        tree = file1[tree_dir]
    except FileNotFoundError:
        print("Could not find file", file_name)
        return
    return tree


def find_event_idx(tree, run, evt):
    runs = tree["run"].array(library="np")
    events = tree["event"].array(library="np")
    run_event = np.vstack((runs, events)).T

    event_idx = np.where((run_event[:, 0] == run) & (run_event[:, 1] == evt))[0]

    if len(event_idx) == 1:
        print("Found unique run/event match at index", event_idx[0])
    else:
        print("No or too many matches found! matches =", event_idx)
        event_idx = None

    return event_idx


def plot_spacepoints(tree, event_idx, run, evt, truth, reco, daughter):

    # Reconstructed primary beam particle
    reco_beam_x = tree["reco_beam_spacePts_X"].array(library="np")[event_idx][0]
    reco_beam_y = tree["reco_beam_spacePts_Y"].array(library="np")[event_idx][0]
    reco_beam_z = tree["reco_beam_spacePts_Z"].array(library="np")[event_idx][0]

    # Truth primary beam particle
    truth_beam_x = tree["truth_beam_spacePts_X"].array(library="np")[event_idx][0]
    truth_beam_y = tree["truth_beam_spacePts_Y"].array(library="np")[event_idx][0]
    truth_beam_z = tree["truth_beam_spacePts_Z"].array(library="np")[event_idx][0]

    # Reconstructed daughters of the primary beam particle
    reco_daughter_x = tree["reco_daughter_spacePts_X"].array(library="np")[event_idx][0]
    reco_daughter_y = tree["reco_daughter_spacePts_Y"].array(library="np")[event_idx][0]
    reco_daughter_z = tree["reco_daughter_spacePts_Z"].array(library="np")[event_idx][0]

    # Truth daughters of the primary beam particle
    truth_daughter_x = tree["truth_daughter_spacePts_X"].array(library="np")[event_idx][0]
    truth_daughter_y = tree["truth_daughter_spacePts_Y"].array(library="np")[event_idx][0]
    truth_daughter_z = tree["truth_daughter_spacePts_Z"].array(library="np")[event_idx][0]

    reco_beam_pdg = tree["primary_pdg"].array(library="np")[event_idx][0]
    reco_daughter_pdg = tree["reco_daughter_pdg"].array(library="np")[event_idx][0]
    truth_daughter_pdg = tree["truth_daughter_pdg"].array(library="np")[event_idx][0]

    if len(reco_beam_x) < 1:
        print("Empty event, skipping plots!")
        return

    fig = go.Figure()
    skip_electron = True

    # Plot the reco beam particle
    if reco:
        print(reco_beam_pdg)
        util.reco_beam_marker['color'] = util.colors[reco_beam_pdg]
        fig.add_trace(go.Scatter3d(x=reco_beam_x,
                                   y=reco_beam_y,
                                   z=reco_beam_z,
                                   name=util.pdg2string[reco_beam_pdg],
                                   mode='lines+markers',
                                   marker=util.reco_beam_marker
                                   )
                      )

    # Plot the truth beam particle
    if truth:
        print(reco_beam_pdg)
        util.truth_beam_marker['color'] = util.colors[reco_beam_pdg]
        fig.add_trace(go.Scatter3d(x=truth_beam_x,
                                   y=truth_beam_y,
                                   z=truth_beam_z,
                                   name=util.pdg2string[reco_beam_pdg],
                                   mode='lines+markers',
                                   marker=util.truth_beam_marker
                                   )
                      )

    # Plot the reco daughter tracks
    if reco and daughter:
        for x, y, z, pdg in zip(reco_daughter_x, reco_daughter_y, reco_daughter_z, reco_daughter_pdg):
            print("Daughter PDG", pdg)
            util.reco_daughter_marker['color'] = util.colors[pdg]
            fig.add_trace(go.Scatter3d(x=np.asarray(x),
                                       y=np.asarray(y),
                                       z=np.asarray(z),
                                       name=util.pdg2string[pdg],
                                       mode='lines+markers',
                                       marker=util.reco_daughter_marker
                                       )
                          )

    # Plot the truth daughter tracks
    if truth and daughter:
        for x, y, z, pdg in zip(truth_daughter_x, truth_daughter_y, truth_daughter_z, truth_daughter_pdg):
            if pdg == 11 and skip_electron: continue # all the electrons clutter so optional skip
            util.truth_daughter_marker['color'] = util.colors.setdefault(pdg, 0)
            fig.add_trace(go.Scatter3d(x=np.asarray(x),
                                       y=np.asarray(y),
                                       z=np.asarray(z),
                                       name=util.pdg2string.setdefault(pdg, 'Unknown'),
                                       mode='lines+markers',
                                       marker=util.truth_daughter_marker
                                       )
                          )

    title = "Run " + str(run) + " event " + str(evt)
    fig.update_layout(title=title, showlegend=True, legend={'itemsizing': 'constant'})
    fig.show()


def plot_event(file, tree_dir, run, evt, truth, reco, daughter):
    tree = open_file(file, tree_dir)
    if tree is None:
        return

    idx = find_event_idx(tree, run, evt)
    if idx is None:
        return

    plot_spacepoints(tree, idx, run, evt, truth, reco, daughter)


########################################

if len(sys.argv) == 4:
    file = sys.argv[1]
    run = sys.argv[1]
    event = sys.argv[1]
else:
    print("None or too many arguements using defaults. Num arguements =", len(sys.argv)-1)

file = "../../spacepoints_run_38308954_evt_332_n10_v2.root"
tree_directory = "trkUtil/points;1"
run = 38308954
event = 332


plot_event(file, tree_directory, run, event, truth=True, reco=True, daughter=True)


