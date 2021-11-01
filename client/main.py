import aiohttp
import asyncio
import torch
from tqdm import tqdm
import typing as tp


from config import *
from utils import TData, load_data, group_data, parse_args


def make_update_vectors_request(data: TData) -> tp.Dict[str, tp.Any]:
    return {
        "banner_ids": data[BANNER_ID].numpy().tolist(),
        "banner_features": {
            feature: data[feature].numpy().tolist()
            for feature in BANNER_FEATURES
        }
    }


def make_get_banners_request(data: TData, top_k: int) -> tp.Dict[str, tp.Any]:
    return {
        "top_k": top_k,
        "hit_features": {
            feature: data[feature].numpy().tolist()[0]
            for feature in HIT_FEATURES
        }
    }


async def main():
    args = parse_args()

    scores = []

    for group in tqdm(group_data(load_data(args.data_path))):
        target = sum(group[t].log() for t in TARGETS)
        update_vectors_request = make_update_vectors_request(data=group)
        top_k = target.shape[0] // 4
        get_banners_request = make_get_banners_request(data=group, top_k=top_k)

        expected_banner_ids = set(group[BANNER_ID][torch.argsort(target)].numpy().tolist()[-top_k:])

        async with aiohttp.ClientSession() as session:
            async with session.post(f'http://{args.host}:{args.port}/reset') as resp:
                assert resp.status == 200, str(resp)

            async with session.post(f'http://{args.host}:{args.port}/update_vectors', json=update_vectors_request) as resp:
                assert resp.status == 200, str(resp)

            async with session.post(f'http://{args.host}:{args.port}/get_banners', json=get_banners_request) as resp:
                assert resp.status == 200, str(resp)
                message = await resp.json(content_type=None)
                assert message['status'] == 'success', str(message)
                given_banner_ids = set(message['data'])
                assert len(given_banner_ids) == top_k

                score = len(given_banner_ids.intersection(expected_banner_ids)) / top_k
                scores.append(score)

    print(sum(scores) / len(scores))

if __name__ == '__main__':
    asyncio.run(main())
