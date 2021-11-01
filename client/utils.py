import argparse
from collections import defaultdict
import torch
import typing as tp

from config import HIT_LOG_ID


TData = tp.Dict[str, torch.Tensor]


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('--data_path', type=str)
    parser.add_argument('--host', type=str)
    parser.add_argument('--port', type=int)
    return parser.parse_args()


def load_data(path: str) -> TData:
    return torch.load(path)


def group_data(data):
    groups = defaultdict(list)
    for i, x in enumerate(data[HIT_LOG_ID].numpy().tolist()):
        groups[x].append(i)

    for _, group_ids in groups.items():
        yield {
            key: val[group_ids]
            for key, val in data.items()
        }
