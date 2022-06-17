#if HAVE_CONFIG_H
# include "config.h"
#endif

#include <libtasn1.h>

const asn1_static_node spnego_asn1_conf[] = {
  { "SPNEGO", 536872976, NULL },
  { NULL, 1073741836, NULL },
  { "MechType", 1073741836, NULL },
  { "MechTypeList", 1610612747, NULL },
  { NULL, 2, "MechType"},
  { "ContextFlags", 1610874886, NULL },
  { "delegFlag", 1073741825, "0"},
  { "mutualFlag", 1073741825, "1"},
  { "replayFlag", 1073741825, "2"},
  { "sequenceFlag", 1073741825, "3"},
  { "anonFlag", 1073741825, "4"},
  { "confFlag", 1073741825, "5"},
  { "integFlag", 1, "6"},
  { "NegHints", 1610612741, NULL },
  { "hintName", 1610637339, NULL },
  { NULL, 2056, "0"},
  { "hintAddress", 536895495, NULL },
  { NULL, 2056, "1"},
  { "NegTokenInitWin", 1610612741, NULL },
  { "mechTypes", 1610620930, "MechTypeList"},
  { NULL, 2056, "0"},
  { "reqFlags", 1610637314, "ContextFlags"},
  { NULL, 2056, "1"},
  { "mechToken", 1610637319, NULL },
  { NULL, 2056, "2"},
  { "negHints", 536895490, "NegHints"},
  { NULL, 2056, "3"},
  { "NegTokenInit", 1610612741, NULL },
  { "mechTypes", 1610620930, "MechTypeList"},
  { NULL, 2056, "0"},
  { "reqFlags", 1610637314, "ContextFlags"},
  { NULL, 2056, "1"},
  { "mechToken", 1610637319, NULL },
  { NULL, 2056, "2"},
  { "mechListMIC", 536895495, NULL },
  { NULL, 2056, "3"},
  { "NegTokenResp", 1610612741, NULL },
  { "negResult", 1610899477, NULL },
  { NULL, 1073743880, "0"},
  { "accept_completed", 1073741825, "0"},
  { "accept_incomplete", 1073741825, "1"},
  { "reject", 1073741825, "2"},
  { "request-mic", 1, "3"},
  { "supportedMech", 1610637314, "MechType"},
  { NULL, 2056, "1"},
  { "responseToken", 1610637319, NULL },
  { NULL, 2056, "2"},
  { "mechListMIC", 536895495, NULL },
  { NULL, 2056, "3"},
  { "NegotiationToken", 1610612754, NULL },
  { "negTokenInit", 1610620930, "NegTokenInit"},
  { NULL, 2056, "0"},
  { "negTokenResp", 536879106, "NegTokenResp"},
  { NULL, 2056, "1"},
  { "NegotiationTokenWin", 1610612754, NULL },
  { "negTokenInit", 536879106, "NegTokenInitWin"},
  { NULL, 2056, "0"},
  { "GSSAPIContextToken", 536879109, NULL },
  { NULL, 1073746952, "0"},
  { "thisMech", 1073741826, "MechType"},
  { "spnego", 2, "NegotiationToken"},
  { NULL, 0, NULL }
};
